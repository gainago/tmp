#include <QScreen>
#include "qapplication.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include "getqstringfromnewwidget.h"

getQStringFromNewWidget::getQStringFromNewWidget() {}

void getQStringFromNewWidget::getString(QString informationLabel, QString informationPushButton)
{
    wgAsk_ = new QWidget;
    QLabel* labelInfo = new QLabel(informationLabel);
    lineEdit_ = new QLineEdit();
    QPushButton* pushButton = new QPushButton(informationPushButton);
    QVBoxLayout* vLayout = new QVBoxLayout;

    vLayout->addWidget(labelInfo);
    vLayout->addWidget(lineEdit_);
    vLayout->addWidget(pushButton);


    wgAsk_->setLayout(vLayout);

    connect(pushButton, SIGNAL(clicked(bool))
            , this, SLOT(ButtonClicked()));

    QRect screen(QRect(QApplication::screens().at(0)->geometry()));
    wgAsk_->move(screen.width() / 2, screen.height() / 2);

    wgAsk_->show();

}

void getQStringFromNewWidget::ButtonClicked()
{
    QString tmpStr = lineEdit_->text();
    emit ButtonPushed(tmpStr);
    delete this;
}
getQStringFromNewWidget::~getQStringFromNewWidget()
{
    delete wgAsk_;
}
