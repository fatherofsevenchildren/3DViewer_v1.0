#include "gif.h"

#include <math.h>

const int width = 256;
const int height = 256;
uint8_t image[width * height * 4];

void SetPixel(int xx, int yy, uint8_t red, uint8_t grn, uint8_t blu) {
  uint8_t* pixel = &image[(yy * width + xx) * 4];
  pixel[0] = red;
  pixel[1] = blu;
  pixel[2] = grn;
  pixel[3] = 255;  // no alpha for this demo
}

void SetPixelFloat(int xx, int yy, float fred, float fgrn, float fblu) {
  // convert float to unorm
  uint8_t red = (uint8_t)roundf(255.0f * fred);
  uint8_t grn = (uint8_t)roundf(255.0f * fgrn);
  uint8_t blu = (uint8_t)roundf(255.0f * fblu);

  SetPixel(xx, yy, red, grn, blu);
}

int giveMeGif(int argc, const char* argv[]) {
  const char* filename = "./MyGif.gif";
  if (argc > 1) {
    filename = argv[1];
  }

  // Create a gif
  GifWriter writer = {};
  GifBegin(&writer, filename, width, height, 2, 8, true);

  for (int frame = 0; frame < 256; ++frame) {
    // Make an image, somehow
    // this is the default shadertoy - credit to shadertoy.com
    float tt = frame * 3.14159f * 2 / 255.0f;
    for (int yy = 0; yy < height; ++yy) {
      for (int xx = 0; xx < width; ++xx) {
        float fx = xx / (float)width;
        float fy = yy / (float)height;

        float red = 0.5f + 0.5f * cosf(tt + fx);
        float grn = 0.5f + 0.5f * cosf(tt + fy + 2.f);
        float blu = 0.5f + 0.5f * cosf(tt + fx + 4.f);

        SetPixelFloat(xx, yy, red, grn, blu);
      }
    }

    // Write the frame to the gif
    printf("Writing frame %d...\n", frame);
    GifWriteFrame(&writer, image, width, height, 2, 8, true);
  }

  // Write EOF
  GifEnd(&writer);

  return 0;
}

bool GifBegin(GifWriter* writer, const char* filename, uint32_t width,
              uint32_t height, uint32_t delay, int32_t bitDepth, bool dither) {
  (void)bitDepth;
  (void)dither;  // Mute "Unused argument" warnings
#if defined(_MSC_VER) && (_MSC_VER >= 1400)
  writer->f = 0;
  fopen_s(&writer->f, filename, "wb");
#else
  writer->f = fopen(filename, "wb");
#endif
  if (!writer->f) return false;

  writer->firstFrame = true;

  // allocate
  writer->oldImage = (uint8_t*)GIF_MALLOC(width * height * 4);

  fputs("GIF89a", writer->f);

  // screen descriptor
  fputc(width & 0xff, writer->f);
  fputc((width >> 8) & 0xff, writer->f);
  fputc(height & 0xff, writer->f);
  fputc((height >> 8) & 0xff, writer->f);

  fputc(0xf0,
        writer->f);     // there is an unsorted global color table of 2 entries
  fputc(0, writer->f);  // background color
  fputc(0, writer->f);  // pixels are square (we need to specify this because
                        // it's 1989)

  // now the "global" palette (really just a dummy palette)
  // color 0: black
  fputc(0, writer->f);
  fputc(0, writer->f);
  fputc(0, writer->f);
  // color 1: also black
  fputc(0, writer->f);
  fputc(0, writer->f);
  fputc(0, writer->f);

  if (delay != 0) {
    // animation header
    fputc(0x21, writer->f);           // extension
    fputc(0xff, writer->f);           // application specific
    fputc(11, writer->f);             // length 11
    fputs("NETSCAPE2.0", writer->f);  // yes, really
    fputc(3, writer->f);              // 3 bytes of NETSCAPE2.0 data

    fputc(1, writer->f);  // JUST BECAUSE
    fputc(0, writer->f);  // loop infinitely (byte 0)
    fputc(0, writer->f);  // loop infinitely (byte 1)

    fputc(0, writer->f);  // block terminator
  }

  return true;
}
