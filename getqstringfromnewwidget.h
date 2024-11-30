#ifndef GETQSTRINGFROMNEWWIDGET_H
#define GETQSTRINGFROMNEWWIDGET_H

#include <QObject>
#include <QLineEdit>


class getQStringFromNewWidget : public QObject
{
    Q_OBJECT
private:
    QLineEdit* lineEdit_;
    QWidget* wgAsk_;
public:
    getQStringFromNewWidget();
    void getString(QString informationLabel, QString informationPushButton);
    ~getQStringFromNewWidget();
public slots:
    void ButtonClicked();
signals:
    void ButtonPushed(QString messageFromUser);
};

#endif // GETQSTRINGFROMNEWWIDGET_H
