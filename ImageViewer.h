#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>

class ImageViewer {
public:
    ImageViewer();
    void setImage(const QPixmap &pixmap) const;
    void showDialog() const;

private:
    QDialog *imageDialog;
    QLabel *imageLabel;
};

#endif // IMAGEVIEWER_H