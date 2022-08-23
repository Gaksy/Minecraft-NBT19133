#include "NBT19133.h"

//NBT19133::NBT19133_ErrorType
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NBT19133::NBT19133_ErrorType::NBT19133_ErrorType(
	const std::string& SOURCE__ERROR_CLASS,
	const std::string& SOURCE__ERROR_FUNC,
	const std::string& SOURCE__ERROR_INFO
) :	errorClass(SOURCE__ERROR_CLASS), 
	errorFunction(SOURCE__ERROR_FUNC), 
	errorInFo(SOURCE__ERROR_INFO) 
{
	;
}
NBT19133::NBT19133_ErrorType::~NBT19133_ErrorType(void) {
	;
}

//NBT19133::TagBase
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NBT19133::TagBase::TagBase(
	const __PRIV_TYPE_TAG_ID SOURCE__TAG_ID,
	const __PRIV_TYPE_TAG_NAME SOURCE__TAG_NAME
) :tagID(SOURCE__TAG_ID) {
	if (!this->setTag_Name(SOURCE__TAG_NAME))
		throw NBT19133_ErrorType(
			"TagBase",
			"NBT19133::TagBase::TagBase(const __PRIV_TYPE_TAG_ID SOURCE__TAG_ID,const __PRIV_TYPE_TAG_NAME SOURCE__TAG_NAME",
			"this->setTag_Name return false"
		);
}
NBT19133::TagBase::TagBase(const __PRIV_TYPE_TAG_ID SOURCE__TAG_ID):tagID(SOURCE__TAG_ID) {
	;
}
NBT19133::TagBase::TagBase(const TagBase& SOURCE__TAG) :tagID(SOURCE__TAG.tagID) {
	this->operator=(SOURCE__TAG);
}
NBT19133::TagBase::~TagBase(void) {
	;
}

NBT19133::TagBase& NBT19133::TagBase::operator=(const NBT19133::TagBase& SOURCE__TAG) {
	if (this->operator==(SOURCE__TAG)) { return *this; }					//检查是否相同

	if (SOURCE__TAG.tagID != this->tagID)									//检查ID是否相同
		throw NBT19133_ErrorType(											//	|
			"TagBase",														//	:
			"NBT19133::TagBase& NBT19133::TagBase::operator=(const NBT19133::TagBase& SOURCE__TAG)",
			"this->tagId 与 SOURCE_TAG.tagId不符"							//	:
		);																	//	|_ true		不相同，抛出异常

	if (!this->setTag_Name(SOURCE__TAG.tagName))							//检查设置标签名是否成功
		throw NBT19133_ErrorType(											//	|
			"TagBase",														//	:
			"NBT19133::TagBase& NBT19133::TagBase::operator=(const NBT19133::TagBase& SOURCE__TAG)",
			"未知错误，SOURCE__TAG.tagName未复制到this->tagName成功"		//	:
		);																	//	|_ true		设置失败，抛出异常

	return *this;
}
bool NBT19133::TagBase::operator==(const NBT19133::TagBase& SOURCE__TAG)const {
	if (&SOURCE__TAG == this) { return true; }								//检查是否是本身
	
	bool check_TagName = false, check_TagId = false;						//设置检查项

	//检查项 TagName
	if (this->tagName == SOURCE__TAG.tagName				||				//检查标签名是否相同
		this->tagName.empty() == SOURCE__TAG.tagName.empty()				//检查是否都为空
		) {																	//	| ||
		check_TagName = true;												//	|_ true		检查通过 赋值检查项 true
	}
	if (this->tagID == SOURCE__TAG.tagID) {									//检查标签ID是否相同
		check_TagId = true;													//	|_ true		检查通过 赋值检查项 true
	}

	if (check_TagName && check_TagId) { return true; }						//如果检查项都通过，返回true
	return false;															//检查未通过 返回false
}
bool NBT19133::TagBase::setTag_Name(const __PRIV_TYPE_TAG_NAME& SOURCE__TAG_NAME) {
	if (NBT19133::__priv_check_TagNameCopy(SOURCE__TAG_NAME)) {				//检查名称是否符合规定
		tagName = SOURCE__TAG_NAME;											//	|_ true		复制名称
		return true;														//	|			返回 true
	}																		//	|
	return false;															//	|_ false	返回 false
}
bool NBT19133::TagBase::getTag_Name(__PRIV_TYPE_TAG_NAME& targetTagName)const {
	if (NBT19133::__priv_check_TagNameRead(targetTagName,this->tagName)) {	//检查是否满足所有复制条件
		targetTagName = this->tagName;										//	|_ true		复制到目标
		return true;														//	|			返回 true
	}																		//	|
	return false;															//	|_ false	返回 false
}
__PRIV_TYPE_TAG_ID NBT19133::TagBase::getTag_ID(void)const {
	return this->tagID;
}
bool NBT19133::TagBase::emptyTag_Name(void)const {
	return this->tagName.empty();
}
void NBT19133::TagBase::clearTag_Name(void) {
	this->tagName.clear();
	return;
}


