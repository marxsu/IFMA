#include "test.h"
#include "ui_test.h"

test::test(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::test)
{
    ui->setupUi(this);
    ui->mLedHight->setText("f0");
    ui->mLedLow->setText("0f");
//    ui->mbindi->setText("5000");
    ui->mPmwHz->setText("255");
    this->setAttribute(Qt::WA_DeleteOnClose);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(onOkButtonOnClick()));
}

test::~test()
{
    delete ui;
}
int test::getLedHight()
{
    return ui->mLedHight->text().toInt(0,16);
}

int test::getLedLow()
{
    return ui->mLedLow->text().toInt(0,16);
}
int test::getLedSymbol()
{
    return ui->mLedSymbol->text().toInt(0,16);
}
int test::getPmwDirection()
{
    return ui->mPmwDirection->text().toInt(0,16);
}
int test::getPmwEnable()
{
    return ui->mPmwEnable->text().toInt(0,16);
}
int test::getPmwHz()
{
    return ui->mPmwHz->text().toInt(0,16);
}
int test::getSpiSymbol()
{
    return ui->mSpiSymbol->text().toInt(0,16);
}
int test::getSwdr()
{
    return ui->mSwdr->text().toInt(0,16);
}
int test::getbindi()
{
    return ui->mbindi->text().toInt();
}

void test::onOkButtonOnClick()
{
    emit okTest(getLedHight(),getLedLow(),getLedSymbol(),getPmwDirection(),getPmwEnable(),getPmwHz(),getSpiSymbol(),getSwdr(),getbindi());
    this->close();
}
