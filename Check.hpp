#ifndef CHECK_HPP
#define CHECK_HPP

#include <QPointF>

/** Information for the printing and layout of a check */
typedef struct Check
{
	/** Location of the Pay To Field */
	QPointF paytoLoc;
	
	/** Location of the decimal amount field */
	QPointF amountLoc;
	
	/* Location of the date field */
	QPointF dateLoc;
	
	/* Location of the dollar amount field */
	QPointF dollarAmountLoc;
	
	/* Location of the memo field */
	QPointF memoLoc;
	
	QString name;
	
	friend QDataStream& operator<< (QDataStream& stream, const Check& check)
	{
		stream << check.name;
		stream << check.paytoLoc;
		stream << check.amountLoc; 
		stream << check.dateLoc ;
		stream << check.dollarAmountLoc;
		stream << check.memoLoc;
		
		return stream;
	}
	
	friend QDataStream& operator>> (QDataStream& stream, Check& check)
	{
		stream >> check.name;
		stream >> check.paytoLoc;
		stream >> check.amountLoc;
		stream >> check.dateLoc;
		stream >> check.dollarAmountLoc;
		stream >> check.memoLoc;
	
		return stream;
	}
	
} Check;

#endif /* CHECK_HPP */
