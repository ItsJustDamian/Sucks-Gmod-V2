#pragma once
#include "../MainHeader.h"
class CLogger
{
private:
	const std::string currentDateTime();
	const char* ConvertMsg(const char* msg);
public:
	void Log(const char* msg);
	void ErrorMsg(const char* msg);
	void WarningMsg(const char* msg);
	void WriteLogFile(const char* msg);
	void ForceColor(int color);
	void ForceResetColor();
};

inline CLogger * Logger;