#include "QCheck.hpp"

#include <QDate>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>

#include <QFile>

#include "CheckSetup.hpp"

#define CHECK_FILE	"checks.qcd"

const char* singles[] = {
	"Zero",
	"One",
	"Two",
	"Three",
	"Four",
	"Five",
	"Six",
	"Seven",
	"Eight",
	"Nine",
	"Ten",
	"Eleven",
	"Twelve",
	"Thirteen",
	"Fourteen",
	"Fifteen",
	"Sixteen",
	"Seventeen",
	"Eighteen",
	"Nineteen",
};

const char* doubles[] = {
	"Twenty",
	"Thirty",
	"Fourty",
	"Fifty",
	"Sixty",
	"Seventy",
	"Eighty",
	"Ninety",
};

const char* magnitudes[] = {
	"Thousand",
	"Million",
	"Billion"
};

QCheck::QCheck() :
	QMainWindow()
{
	setupUi(this);
	
	dateField->setText(QDate::currentDate().toString("MM/dd/yyyy"));
	
	Check current;
	
	//read check styles from file
	QFile checks(CHECK_FILE);
	if (checks.open(QIODevice::ReadOnly))
	{
		QDataStream fin(&checks);
		while (!checks.atEnd())
		{
			fin >> current;
			_checks.append(current);
			availChecks->addItem(current.name);
		}
		
		checks.close();
	}
}

QCheck::~QCheck()
{
	
}

void QCheck::closeEvent(QCloseEvent* ce)
{
	//write check styles to file
	QFile checks(CHECK_FILE);
	if (checks.open(QIODevice::WriteOnly))
	{
		QDataStream fout(&checks);
		
		for (int i=0 ; i<_checks.size() ; ++i)
		{
			fout << _checks[i];
		}
		
		checks.close();
	}
}

void QCheck::on_amountField_textChanged()
{
	bool ok;
	float num = amountField->text().toFloat(&ok);
	
	if (ok)
	{
		dollarAmntLabel->setText(textualNum(num));
	}
	else
	{
		dollarAmntLabel->setText("Enter A monetary amount.");
	}
}

QString QCheck::textualNum(float decNum)
{
	QString final;
	
	//look at 3 digits at a time
	
	int mag = -1;
	int number = (int)decNum;
	while (number > 0)
	{
		QString text;
		int num = number % 1000;
		
		if (num >= 100)
		{
			text += singles[num/100];
			text += " Hundred ";
		}
		
		num %= 100;
		
		//first look at tens and ones place
		if (num >= 20)
		{
			//tens place needs to combine with ones place
			text += doubles[num / 10 - 2];
			
			if (num % 10 != 0 )
			{
				text += "-";
				text += singles[num%10];
			}
		}
		else if (num <= 20 && num != 0)
		{
			text += singles[num];
		}
			
		if (mag >= 0 && num != 0)
		{
			text += " ";
			text += magnitudes[mag];
			text += " ";
		}
		
		mag++;
			
		number /=1000;
		
		final = text + final;
	}
	
	final += " & " + QString::number(int(decNum*100+.5)%100) + "/100";
	
	return final;
}

void QCheck::on_printButton_clicked()
{
	QPrinter printer;
	
	QPrintDialog dialog(&printer, this);
	dialog.setWindowTitle(tr("Print Check"));
	if (dialog.exec() != QDialog::Accepted)
	{
		return;
	}
	
	printer.setFullPage(true);
	
	//get resolution
	float dpmm = printer.resolution()/25.4f;
	
	//locations in MM from upper left of check
	int index = availChecks->currentIndex();
	if (index >= 0)
	{
		//create and start painting
		QPainter checkPainter;
		checkPainter.begin(&printer);
		
		//set check font
		QFont checkFont = paytoField->font();
		checkFont.setPixelSize(int(4.0 * dpmm + .5)); //4mm height
		checkPainter.setFont(checkFont);
		
		//move so 0,0 is upper corner of page
		//checkPainter.translate(-printer.pageRect().topLeft());
		
		//test check image
		//QImage check("Document.jpg");
		//checkPainter.drawImage(0, 0, check.scaledToWidth(int(149.35*dpmm + .5)));
		
		//load style
		Check _current = _checks[index];
		
		//paint check
		checkPainter.drawText(_current.paytoLoc * dpmm, paytoField->text());
		checkPainter.drawText(_current.dateLoc * dpmm, dateField->text());
		checkPainter.drawText(_current.amountLoc * dpmm, amountField->text());
		checkPainter.drawText(_current.dollarAmountLoc * dpmm, dollarAmntLabel->text());
		checkPainter.drawText(_current.memoLoc * dpmm, memoField->text());
		
		checkPainter.end();
	}
}

void QCheck::on_addButton_clicked()
{
	Check newCheck;
	CheckSetup addDialog(&newCheck, this);
	
	if (addDialog.exec())
	{
		//add the check (vector and combo box)
		_checks.append(newCheck);
		availChecks->addItem(newCheck.name);
	}
}

void QCheck::on_removeButton_clicked()
{
	int index = availChecks->currentIndex();
	if (index >= 0)
	{
		_checks.remove(index);
		availChecks->removeItem(index);
	}
}

void QCheck::on_editButton_clicked()
{
	int index = availChecks->currentIndex();
	if (index >= 0)
	{
		Check edited = _checks[index];
		CheckSetup addDialog(&edited, this);
		
		if (addDialog.exec())
		{
			//accept changes
			_checks[index] = edited;
			availChecks->setItemText(index, edited.name);
		}
	}
}
