#include "ImageViewer.h"

#include <QDir>
#include <qguiapplication.h>
#include <QMessageBox>
#include <QImageReader>

ImageViewer::ImageViewer() {
    imageDialog = new QDialog();
    imageDialog->setWindowTitle("Image Viewer");


    imageLabel = new QLabel(imageDialog);
    auto *layout = new QVBoxLayout(imageDialog);
    layout->addWidget(imageLabel);
    imageDialog->setLayout(layout);
}

void ImageViewer::setImage(const QPixmap &pixmap) const
{
    imageLabel->setPixmap(pixmap);
    // imageLabel->setScaledContents( true );
    imageLabel->setAlignment(Qt::AlignCenter);
    // imageLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
}

void ImageViewer::showDialog() const
{
    imageDialog->resize(1920,1080);
    imageDialog->show();
}
