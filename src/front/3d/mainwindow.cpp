#include "mainwindow.h"

#include "ui_mainwindow.h"

extern "C" {
#include "gif.h"
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->widget->backColor = Qt::gray;
  ui->widget->pro = &pro;
  ui->widget->frame = &frame;
  loadSetts();
  loadChecker();
  if (last_obj == empty)
    helper();
  else
    loadMod(last_obj);
}

MainWindow::~MainWindow() {
  saveSetts();
  cleaner();
  delete ui;
}

void MainWindow::interface(bool a) { ui->tabWidget->setEnabled(a); }

bool MainWindow::helper() {
  bool res = 0;
  QMessageBox::StandardButton my = QMessageBox::question(
      this, "Can't read file", "Do u want try open other file?",
      QMessageBox::Yes | QMessageBox::No);
  if (my == QMessageBox::No)
    interface(false);  // QCoreApplication::quit();
  else
    res = on_loadModelFileButton_clicked();
}

void MainWindow::loadChecker() {
  ui->pnSizeSpinBox->setValue(ui->widget->point_sz);
  ui->lnWidthSpinBox->setValue(ui->widget->line_sz);
  if (!ui->widget->projection)
    ui->radioButton_4->setChecked(1);
  else
    ui->radioButton_5->setChecked(1);
  if (!ui->widget->point_type)
    ui->radio_cube->setChecked(1);
  else
    ui->radio_sphere->setChecked(1);
  if (ui->widget->dashed)
    ui->checkBox_ln_2->setChecked(1);
  else
    ui->checkBox_ln_2->setChecked(0);
  if (ui->widget->points)
    ui->checkBox_pn->setChecked(1);
  else
    ui->checkBox_ln->setChecked(0);
  if (ui->widget->lines)
    ui->checkBox_ln->setChecked(1);
  else
    ui->checkBox_ln->setChecked(0);
}

bool MainWindow::on_loadModelFileButton_clicked() {
  bool res = 0;
  QString filename = QFileDialog::getOpenFileName(
      this, "choose file", QCoreApplication::applicationDirPath(),
      "Text Files (*.obj)");
  if (filename != empty)
    loadMod(filename);
  else
    res = 1;
  return res;
}

int MainWindow::loadMod(QString filename) {
  QByteArray ba = filename.toLocal8Bit();
  char *file = ba.data();
  int res = parser(file, &pro, &frame);
  if (res == 0) {
    interface(1);
    last_obj = filename;
    ui->label->setText(filename);
    int a = pro.vectors_count / 2;
    int b = pro.vertexes_count;
    ui->vectors->setText("Vectors: " + QString::number(a));
    ui->vertex->setText("Vertexes: " + QString::number(b));
  } else {
    ui->label->setText("ERROR. Please try another file");
    //    bool st = 1;
    //    while (res && st!=0){
    res = helper();
    //    }
  }
  ui->widget->update();
  return res;
}

void MainWindow::cleaner() {
  if (pro.vectors) delete[] pro.vectors;
  if (pro.vertexes) delete[] pro.vertexes;
  if (pro.vecs) delete[] pro.vecs;
}

void MainWindow::on_changeBGColorButton_clicked() {
  QColor qcolor = QColorDialog::getColor(Qt::blue, this);
  ui->widget->backColor = qcolor;
  ui->widget->update();
}

void MainWindow::on_checkBox_ln_clicked(bool checked) {
  ui->widget->lines = (checked) ? 1 : 0;
  ui->widget->update();
}

void MainWindow::on_checkBox_pn_clicked(bool checked) {
  ui->widget->points = (checked) ? 1 : 0;
  ui->widget->update();
}

void MainWindow::on_pnSizeSpinBox_valueChanged(double arg1) {
  ui->widget->point_sz = arg1;
  ui->widget->update();
}

void MainWindow::on_radio_sphere_clicked(bool checked) {
  ui->widget->point_type = (checked) ? 1 : 0;
  ui->widget->update();
}

void MainWindow::on_radio_cube_clicked(bool checked) {
  ui->widget->point_type = (checked) ? 0 : 1;
  ui->widget->update();
}

void MainWindow::on_checkBox_ln_2_clicked(bool checked) {
  ui->widget->dashed = (checked) ? 1 : 0;
  ui->widget->update();
}

void MainWindow::on_lnWidthSpinBox_valueChanged(double arg1) {
  ui->widget->line_sz = arg1;
  ui->widget->update();
}

void MainWindow::on_radioButton_4_clicked() {
  ui->widget->projection = 0;
  ui->widget->update();
}

void MainWindow::on_radioButton_5_clicked() {
  ui->widget->projection = 1;
  ui->widget->update();
}

void MainWindow::moveRepeat() {
  verts4vecs(&pro);
  ui->widget->update();
}

void MainWindow::on_edgesColorButton_clicked() {
  QColor qcolor = QColorDialog::getColor(Qt::blue, this);
  ui->widget->lineColor = qcolor;
  ui->widget->update();
}

void MainWindow::on_verticesColorButton_clicked() {
  QColor qcolor = QColorDialog::getColor(Qt::blue, this);
  ui->widget->pointColor = qcolor;
  ui->widget->update();
}

void MainWindow::on_moveRightButton_clicked() {
  Moving(&pro, -0.1, 'x');
  moveRepeat();
}

void MainWindow::on_moveLeftButton_clicked() {
  Moving(&pro, 0.1, 'x');
  moveRepeat();
}

void MainWindow::on_moveDownButton_clicked() {
  Moving(&pro, -0.1, 'y');
  moveRepeat();
}

void MainWindow::on_moveUpButton_clicked() {
  Moving(&pro, 0.1, 'y');
  moveRepeat();
}

void MainWindow::on_moveBackwardButton_clicked() {
  Moving(&pro, -0.1, 'z');
  moveRepeat();
}

void MainWindow::on_moveForwardButton_clicked() {
  Moving(&pro, 0.1, 'z');
  moveRepeat();
}

void MainWindow::on_rotateDownButton_clicked() {
  RotateX(&pro, 0.1);
  moveRepeat();
}

void MainWindow::on_rotateUpButton_clicked() {
  RotateX(&pro, -0.1);
  moveRepeat();
}

void MainWindow::on_rotateLeftButton_clicked() {
  RotateY(&pro, 0.1);
  moveRepeat();
}

void MainWindow::on_rotateRightButton_clicked() {
  RotateY(&pro, -0.1);
  moveRepeat();
}

void MainWindow::on_rotateClockwiseButton_clicked() {
  RotateZ(&pro, -0.1);
  moveRepeat();
}

void MainWindow::on_rotateCounterclockwiseButton_clicked() {
  RotateZ(&pro, 0.1);
  moveRepeat();
}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1) {
  normalization(&pro, &frame);
  scal(&frame, &pro, arg1);
  moveRepeat();
}

void MainWindow::saveSetts() {
  QSettings settings(
      QCoreApplication::applicationDirPath() + "/3d_settings.conf",
      QSettings::NativeFormat);
  settings.setValue("Colors/bg", ui->widget->backColor.name(QColor::HexArgb));
  settings.setValue("Colors/ln", ui->widget->lineColor.name(QColor::HexArgb));
  settings.setValue("Colors/pn", ui->widget->pointColor.name(QColor::HexArgb));
  settings.setValue("Size/point", ui->widget->point_sz);
  settings.setValue("Size/line", ui->widget->line_sz);
  settings.setValue("Proj/proj", ui->widget->projection);
  settings.setValue("Types/pn", ui->widget->point_type);
  settings.setValue("Types/ln", ui->widget->dashed);
  settings.setValue("Exist/pn", ui->widget->points);
  settings.setValue("Exist/ln", ui->widget->lines);
  settings.setValue("Last_file", last_obj);
}

void MainWindow::loadSetts() {
  QSettings settings(
      QCoreApplication::applicationDirPath() + "/3d_settings.conf",
      QSettings::NativeFormat);
  ui->widget->backColor = settings.value("Colors/bg", wh).toString();
  ui->widget->lineColor = settings.value("Colors/ln", bk).toString();
  ui->widget->pointColor = settings.value("Colors/pn", bl).toString();
  ui->widget->line_sz = settings.value("Size/line", 1).toInt();
  ui->widget->point_sz = settings.value("Size/point", 1).toInt();
  ui->widget->projection = settings.value("Proj/proj", 1).toInt();
  ui->widget->point_type = settings.value("Types/pn", 0).toInt();
  ui->widget->dashed = settings.value("Types/ln", 0).toInt();
  ui->widget->points = settings.value("Exist/pn", 0).toInt();
  ui->widget->lines = settings.value("Exist/ln", 1).toInt();
  last_obj = settings.value("Last_file", empty).toString();
}

void MainWindow::on_screencastButton_clicked() {
  QString temp = QCoreApplication::applicationDirPath();
  temp.resize(temp.size() - 38);
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Save gif"), temp + "/images", tr("GIF (*.gif)"));
  if (!fileName.isEmpty()) {
    QImage img(ui->widget->size(), QImage::Format_RGB32);
    QPainter painter(&img);
    QImage img640_480;
    QTime timer;
    int width = 640, height = 480;
    GifWriter gif;
    QByteArray ba = fileName.toLocal8Bit();
    char *nm = ba.data();
    GifBegin(&gif, nm, width, height, 100);
    for (int i = 0; i < 50; ++i) {
      ui->widget->render(&painter);
      img640_480 = img.scaled(QSize(640, 480));
      GifWriteFrame(&gif, img640_480.bits(), width, height, 100);
      timer = QTime::currentTime().addMSecs(100);
      while (QTime::currentTime() < timer)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    GifEnd(&gif);
    QMessageBox msgBox;
    msgBox.setText("GIF has been saved");
    msgBox.exec();
  } else {
    QMessageBox::warning(this, "", "Save failed");
  }
}

void MainWindow::on_screenshotButton_clicked() {
  QImage img(ui->widget->size(), QImage::Format_RGB32);
  QPainter painter(&img);
  QString tmp = QCoreApplication::applicationDirPath();
  tmp.resize(tmp.size() - 38);
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Save file"), tmp + "/images", tr("JPG (*.jpg);; BMP (*.bmp)"));
  ui->widget->render(&painter);
  if (img.save(fileName)) {
    QMessageBox msgBox;
    msgBox.setText("Screenshot has been saved");
    msgBox.exec();
  } else
    QMessageBox::warning(this, "", "Save failed.");
}
