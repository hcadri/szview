//
// Created by A C on 7/20/24.
//

#ifndef SUPERWIDGET_H
#define SUPERWIDGET_H
#include <QtWidgets/QWidget>


class SuperWidget : public  QWidget
{
    Q_OBJECT
public:
    explicit SuperWidget(QWidget *parent = nullptr);
    ~SuperWidget() override;

    void open(const QString& urlString, bool local = true);

private:
    void setupUi();

    QString urlString;

};



#endif //SUPERWIDGET_H
