#ifndef QCHECK_HPP
#define QCHECK_HPP

#include <QString>
#include <QCloseEvent>

#include <ui_QCheck.h>

#include "Check.hpp"

class QCheck : public QMainWindow, public Ui::QCheck
{
	Q_OBJECT;
	
	public:
		QCheck();
		~QCheck();
	
	private slots:
		void on_amountField_textChanged();
		
		void on_printButton_clicked();
		
		void on_addButton_clicked();
		void on_removeButton_clicked();
		void on_editButton_clicked();
		
	protected:
		void closeEvent(QCloseEvent* ce);
	
	private: //methods
		QString textualNum(float num);
		
		QVector<Check> _checks;
};

#endif
