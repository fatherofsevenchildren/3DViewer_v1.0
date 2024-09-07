#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QTextEdit>
#include <QtCore>

extern "C" {
#include "../../back/parser.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  arr pro = {0, 0, 0, 0, 0, 0};
  minmax_t frame = {0, 0, 0, 0, 0, 0};
  void saveSetts();
  void loadSetts();
  QColor bk = Qt::black, bl = Qt::blue, wh = Qt::white;
  //  QString path = "./models";
  QString start = "./alf.obj", last_obj, empty;
  //  int result = 0;

 private slots:

  void interface(bool a);

  bool on_loadModelFileButton_clicked();

  int loadMod(QString filename);

  bool helper();

  void loadChecker();

  void moveRepeat();

  void on_changeBGColorButton_clicked();

  void on_checkBox_ln_clicked(bool checked);

  void on_checkBox_pn_clicked(bool checked);

  void on_pnSizeSpinBox_valueChanged(double arg1);

  void on_radio_sphere_clicked(bool checked);

  void on_radio_cube_clicked(bool checked);

  void on_checkBox_ln_2_clicked(bool checked);

  void cleaner();

  void on_lnWidthSpinBox_valueChanged(double arg1);

  void on_radioButton_4_clicked();

  void on_radioButton_5_clicked();

  void on_edgesColorButton_clicked();

  void on_verticesColorButton_clicked();

  void on_moveRightButton_clicked();

  void on_moveLeftButton_clicked();

  void on_moveDownButton_clicked();

  void on_moveUpButton_clicked();

  void on_moveBackwardButton_clicked();

  void on_moveForwardButton_clicked();

  void on_rotateDownButton_clicked();

  void on_rotateUpButton_clicked();

  void on_rotateLeftButton_clicked();

  void on_rotateRightButton_clicked();

  void on_rotateClockwiseButton_clicked();

  void on_rotateCounterclockwiseButton_clicked();

  void on_doubleSpinBox_valueChanged(double arg1);

  void on_screencastButton_clicked();

  void on_screenshotButton_clicked();

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
