#include "Logger.h"

const std::string CLogger::currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

	return buf;
}

const char * CLogger::ConvertMsg(const char * msg)
{
	std::stringstream ss;
	ss << currentDateTime() << ">> " << msg << "\n";
	return ss.str().c_str();
}

void CLogger::Log(const char * msg)
{
	ForceColor(7);
	char buffer[2048];
	sprintf(buffer, "%s >> %s\n", currentDateTime().c_str(), msg);
	printf(buffer);
	WriteLogFile(buffer);
}

void CLogger::ErrorMsg(const char * msg)
{
	ForceColor(4);
	char buffer[2048];
	sprintf(buffer, "%s >> %s\n", currentDateTime().c_str(), msg);
	printf(buffer);
	WriteLogFile(buffer);
}

void CLogger::WarningMsg(const char * msg)
{
	ForceColor(14);
	char buffer[2048];
	sprintf(buffer, "%s >> %s\n", currentDateTime().c_str(), msg);
	printf(buffer);
	WriteLogFile(buffer);
}

void CLogger::WriteLogFile(const char * msg)
{
	/*std::ofstream ofs("Sucks_Logs.txt", std::ios_base::out || std::ios_base::app);

	if (!ofs)
	{
		ErrorMsg("Failed to open log file!");
	}

	ofs << msg;
	ofs.close();*/
}

void CLogger::ForceColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void CLogger::ForceResetColor()
{
	ForceColor(7);
}
