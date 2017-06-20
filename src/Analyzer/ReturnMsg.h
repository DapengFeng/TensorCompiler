#pragma once

#include <qstring.h>

class ReturnMsg
{
public:
	QString msgType;
	QString msgContent;

	static QString ERROR;
	static QString START;
	static QString SUCCESS;
	static QString DELETE;
	static QString ASSIGN;

public:
	ReturnMsg();
	~ReturnMsg();
};