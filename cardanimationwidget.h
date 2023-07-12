#ifndef CARDANIMATIONWIDGET_H
#define CARDANIMATIONWIDGET_H

#include <QWidget>
#include <apimethods.h>

QT_BEGIN_NAMESPACE
namespace Ui { class CardAnimationWidget; }
QT_END_NAMESPACE

class CardAnimationWidget : public QWidget
{
    Q_OBJECT

public:
    CardAnimationWidget(QWidget *parent = nullptr);
    ~CardAnimationWidget();

private:
    Ui::CardAnimationWidget *ui;
};
#endif // CARDANIMATIONWIDGET_H
