#ifndef CUSTOMIZECANNYDETECTION_H
#define CUSTOMIZECANNYDETECTION_H

#include <QMainWindow>
#include "imageprocessing.h"

namespace Ui {
class CustomizeCannyDetection;
}

class CustomizeCannyDetection : public QMainWindow
{
    Q_OBJECT

public:
    explicit CustomizeCannyDetection(QWidget *parent = nullptr);
    ~CustomizeCannyDetection();

    void setImageObject (ImageProcessing* img);
private slots:
    void on_sliderMinThreshold_valueChanged(int value);

    void on_sliderMaxThreshold_valueChanged(int value);

    void on_butViewCannyImage_clicked();

private:
    Ui::CustomizeCannyDetection *ui;
};

#endif // CUSTOMIZECANNYDETECTION_H
