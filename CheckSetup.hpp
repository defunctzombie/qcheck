#ifndef CHECKSETUP_HPP
#define CHECKSETUP_HPP

#include <ui_CheckSetup.h>

#include "Check.hpp"

class CheckSetup : public QDialog, public Ui::CheckSetup
{
	Q_OBJECT;
	
	public:
		CheckSetup(Check* check, QWidget* parent = NULL);
		~CheckSetup();
		
	protected slots:
		void on_diagOptions_accepted();
		
	private:
		Check* _check;
};

#endif /* CHECKSETUP_HPP */
