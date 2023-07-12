#include "cardanimationwidget.h"
#include "ui_cardanimationwidget.h"

CardAnimationWidget::CardAnimationWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CardAnimationWidget)
{
    ui->setupUi(this);

    ApiCardConnector* data = new ApiCardConnector();
    ui->name->setText(data->getName());
    ui->description->setText(data->getDescription());
    ui->image->setPixmap(data->getImage());
}

CardAnimationWidget::~CardAnimationWidget()
{
    delete ui;
}
