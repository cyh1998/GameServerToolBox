#ifndef LOADXMLBASE_H
#define LOADXMLBASE_H

#include <string>
#include <map>
#include <functional>
#include <sys/time.h>

class LoadXmlBase 
{
public:
	using readCallBack = std::function<bool(void)>;
	struct tagSheet
	{
		bool m_bCanEmpty = false;
		readCallBack m_readCallBack = nullptr;
	};

public:
	virtual ~LoadXmlBase() {}

	void setFileName(std::string fileName) { m_fileName = fileName; }
	std::string getFileName() { return m_fileName; }

	bool loadXmlData(const char * fileName);
	void setSheetReadCallBack(const char * sheetName, readCallBack cb, bool bCanEmpty = false);
	
	std::string getDataStr(const char * field, const std::string & def = "");
	int32_t getDataInt(const char * field, const int32_t def = 0);
	bool getDataBool(const char * field, const bool def = false);
	double getDataFloat(const char * field, const double def = 0.0f);
	time_t getDataTime(const char * field, const time_t def = 0);
	uint32_t getDataUInt(const char * field, const uint32_t def = 0);
	int64_t getDataInt64(const char * field, const int64_t def = 0);

private:
	bool readData(const char * field, std::string & ret);

private:
	std::string m_fileName;
	std::map<std::string, std::string> m_rowData;
	std::map<std::string, tagSheet> m_sheet;
};

#endif //LOADXMLBASE_H
