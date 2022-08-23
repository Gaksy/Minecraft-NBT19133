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
	if (this->operator==(SOURCE__TAG)) { return *this; }					//����Ƿ���ͬ

	if (SOURCE__TAG.tagID != this->tagID)									//���ID�Ƿ���ͬ
		throw NBT19133_ErrorType(											//	|
			"TagBase",														//	:
			"NBT19133::TagBase& NBT19133::TagBase::operator=(const NBT19133::TagBase& SOURCE__TAG)",
			"this->tagId �� SOURCE_TAG.tagId����"							//	:
		);																	//	|_ true		����ͬ���׳��쳣

	if (!this->setTag_Name(SOURCE__TAG.tagName))							//������ñ�ǩ���Ƿ�ɹ�
		throw NBT19133_ErrorType(											//	|
			"TagBase",														//	:
			"NBT19133::TagBase& NBT19133::TagBase::operator=(const NBT19133::TagBase& SOURCE__TAG)",
			"δ֪����SOURCE__TAG.tagNameδ���Ƶ�this->tagName�ɹ�"		//	:
		);																	//	|_ true		����ʧ�ܣ��׳��쳣

	return *this;
}
bool NBT19133::TagBase::operator==(const NBT19133::TagBase& SOURCE__TAG)const {
	if (&SOURCE__TAG == this) { return true; }								//����Ƿ��Ǳ���
	
	bool check_TagName = false, check_TagId = false;						//���ü����

	//����� TagName
	if (this->tagName == SOURCE__TAG.tagName				||				//����ǩ���Ƿ���ͬ
		this->tagName.empty() == SOURCE__TAG.tagName.empty()				//����Ƿ�Ϊ��
		) {																	//	| ||
		check_TagName = true;												//	|_ true		���ͨ�� ��ֵ����� true
	}
	if (this->tagID == SOURCE__TAG.tagID) {									//����ǩID�Ƿ���ͬ
		check_TagId = true;													//	|_ true		���ͨ�� ��ֵ����� true
	}

	if (check_TagName && check_TagId) { return true; }						//�������ͨ��������true
	return false;															//���δͨ�� ����false
}
bool NBT19133::TagBase::setTag_Name(const __PRIV_TYPE_TAG_NAME& SOURCE__TAG_NAME) {
	if (NBT19133::__priv_check_TagNameCopy(SOURCE__TAG_NAME)) {				//��������Ƿ���Ϲ涨
		tagName = SOURCE__TAG_NAME;											//	|_ true		��������
		return true;														//	|			���� true
	}																		//	|
	return false;															//	|_ false	���� false
}
bool NBT19133::TagBase::getTag_Name(__PRIV_TYPE_TAG_NAME& targetTagName)const {
	if (NBT19133::__priv_check_TagNameRead(targetTagName,this->tagName)) {	//����Ƿ��������и�������
		targetTagName = this->tagName;										//	|_ true		���Ƶ�Ŀ��
		return true;														//	|			���� true
	}																		//	|
	return false;															//	|_ false	���� false
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


