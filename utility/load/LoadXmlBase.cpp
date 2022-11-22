#include <assert.h>
#include <memory>
#include "tinyxml/tinyxml.h"
#include "../func/FuncFile.h"
#include "../base/Log.h"
#include "LoadXmlBase.h"

bool LoadXmlBase::loadXmlData(const char * fileName)
{
	if (nullptr == fileName) {
		return false;
	}

	setFileName(fileName);
	
	std::string strName = get_local_path(fileName);
	std::unique_ptr<TiXmlDocument> pDoc(new TiXmlDocument(strName.c_str()));
	if (!pDoc) {
		// LOG_ERROR("TiXmlDocument %s fail!", strName.c_str());
		return false;
	}

	if (!pDoc->LoadFile()) {
		// LOG_ERROR("Load %s fail!", strName.c_str());
		return false;
	}

	TiXmlElement* pRoot = pDoc->RootElement();
	if (!pRoot) {
		return false;
	}

	TiXmlElement* pElement = pRoot->FirstChildElement();
	while (pElement) 
	{
		m_rowData.clear();
		auto itemSheet = m_sheet.find(pElement->Value());
		if (itemSheet == m_sheet.end() || nullptr == itemSheet->second.m_readCallBack) 
		{
			pElement = pElement->NextSiblingElement();
			continue;
		}

		TiXmlElement* pElementNode = pElement->FirstChildElement();
		while (pElementNode) 
		{
			std::string strKey = pElement->Value();
			auto pText = pElement->GetText();
			std::string strValue = (nullptr ==  pText ? "" : pText);
			
			//TODO 字符串处理
			
			if (strKey.empty()) {
				return false;
			}

			m_rowData.emplace(strKey, strValue);
			pElementNode = pElementNode->NextSiblingElement();
		}

		// 调用callback
		if (!(itemSheet->second.m_readCallBack)()) {
			return false;
		}

		pElement = pElement->NextSiblingElement();
	}

	return true;
}

void LoadXmlBase::setSheetReadCallBack(const char * sheetName, readCallBack cb, bool bCanEmpty)
{
	auto item = m_sheet.find(sheetName);
	if (item != m_sheet.end()) {
		item->second.m_readCallBack = cb;
		item->second.m_bCanEmpty = bCanEmpty;
	} else {
		tagSheet sheet;
		sheet.m_bCanEmpty = bCanEmpty;
		sheet.m_readCallBack = cb;
		m_sheet.emplace(sheetName, sheet);
	}
}

std::string LoadXmlBase::getDataStr(const char * field, const std::string & def)
{
	assert(field);
	std::string strResult;
	if (!readData(field, strResult)) {
		return def;
	}
	return strResult;
}

bool LoadXmlBase::readData(const char * field, std::string & ret)
{
	auto iter = m_rowData.find(field);
	if (iter != m_rowData.end()) {
		ret = iter->second;
		return true;
	}

	return false;
}

