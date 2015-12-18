#include "CheckSetup.hpp"

CheckSetup::CheckSetup(Check* check, QWidget* parent) :
	QDialog(parent)
{
	setupUi(this);
	
	_check = check;
	
	checkNameField->setText(_check->name);
	paytoXField->setText(QString::number(_check->paytoLoc.x()));
	paytoYField->setText(QString::number(_check->paytoLoc.y()));
	
	dateXField->setText(QString::number(_check->dateLoc.x()));
	dateYField->setText(QString::number(_check->dateLoc.y()));
	
	amountXField->setText(QString::number(_check->amountLoc.x()));
	amountYField->setText(QString::number(_check->amountLoc.y()));
	
	amountTextXField->setText(QString::number(_check->dollarAmountLoc.x()));
	amountTextYField->setText(QString::number(_check->dollarAmountLoc.y()));
	
	memoXField->setText(QString::number(_check->memoLoc.x()));
	memoYField->setText(QString::number(_check->memoLoc.y()));
}

CheckSetup::~CheckSetup()
{
	
}

void CheckSetup::on_diagOptions_accepted()
{
	//populate the check
	_check->name = checkNameField->text();
	_check->paytoLoc = QPointF(paytoXField->text().toFloat(), paytoYField->text().toFloat());
	_check->dateLoc = QPointF(dateXField->text().toFloat(), dateYField->text().toFloat());
	_check->amountLoc = QPointF(amountXField->text().toFloat(), amountYField->text().toFloat());
	_check->dollarAmountLoc = QPointF(amountTextXField->text().toFloat(), amountTextYField->text().toFloat());
	_check->memoLoc = QPointF(memoXField->text().toFloat(), memoYField->text().toFloat());
}
