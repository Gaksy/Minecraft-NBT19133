#pragma once
#include <string>

#define MAXSIZE_TAGNAME UINT16_MAX
#define MAXSIZE_TAGARRAY UINT32_MAX
#define MAXSIZE_TAGLIST UINT8_MAX

#define __PRIV_TYPE_TAG_ID uint8_t
#define __PRIV_TYPE_TAG_NAME std::wstring
#define __PRIV_TAG_Byte int8_t
#define __PRIV_TAG_Short int16_t
#define __PRIV_TAG_Int int32_t
#define __PRIV_TAG_Long int64_t
#define __PRIV_TAG_Float float
#define __PRIV_TAG_Double double
#define __PRIV_TAG_Byte_Array TAG_Byte
#define __PRIV_TAG_String std::wstring

namespace NBT19133 {
	class NBT19133_ErrorType {
	public:
		NBT19133_ErrorType(
			const std::string& SOURCE__ERROR_CLASS,
			const std::string& SOURCE__ERROR_FUNC,
			const std::string& SOURCE__ERROR_INFO
		);
		~NBT19133_ErrorType(void);

		const std::string errorClass;
		const std::string errorFunction;
		const std::string errorInFo;
	};

	inline bool __priv_check_TagNameCopy(const __PRIV_TYPE_TAG_NAME& SOURCE__TAG_NAME) {
		if (&SOURCE__TAG_NAME							&&	//����ǩ�����Ƿ����
			!SOURCE__TAG_NAME.empty()					&&	//����ǩ�����Ƿ�Ϊ��
			SOURCE__TAG_NAME.size() <= MAXSIZE_TAGNAME		//����ǩ���ƵĴ�С�Ƿ񳬹�����
			) {												//	|	&&
			return true;									//	|_ true		���� true
		}													//	|
		return false;										//	|_ false	���� false
	}
	inline bool __priv_check_TagNameRead(const __PRIV_TYPE_TAG_NAME& TARGET__TAG_NAME) {
		if (&TARGET__TAG_NAME			&&					//���Ҫ���Ƶ��Ķ����Ƿ����
			TARGET__TAG_NAME.empty()						//���Ҫ���Ƶ��Ķ����Ƿ��ǿյ�
			) {												//	|	&&
			return true;									//	|_ true		���� true
		}													//	|
		return false;										//	|_ false	���� false
	}
	inline bool __priv_check_TagNameRead(
		const __PRIV_TYPE_TAG_NAME& TARGET__TAG_NAME,
		const __PRIV_TYPE_TAG_NAME& SOURCE__TAG_NAME
	) {
		if (NBT19133::__priv_check_TagNameCopy(SOURCE__TAG_NAME) &&	//��鱻���ƵĶ����Ƿ����
			NBT19133::__priv_check_TagNameRead(TARGET__TAG_NAME)	//��鸴�Ƶ��Ķ����Ƿ����
			) {														//	|	&&
			return true;											//	|_ true		���� true
		}															//	|
		return false;												//	|_ false	���� false
	}

	template<typename PAYLOAD_TYPE>
	inline bool __priv_check_TagPayloadCopy(const PAYLOAD_TYPE& SOURCE__PAYLOAD) {
		if (&SOURCE__PAYLOAD) { return true; }											//���Ҫ���ƵĶ����Ƿ����
		return false;
	}
	template<typename PAYLOAD_TYPE>
	inline bool __priv_chech_TagPayloadRead(const PAYLOAD_TYPE& TARGET_PAYLOAD) {
		if (&TARGET_PAYLOAD) { return true; }											//���Ҫ���Ƶ��Ķ����Ƿ����
		return false;
	}
	template<typename PAYLOAD_TYPE>
	inline bool __priv_check_TagPayloadRead(
		const PAYLOAD_TYPE& TARGET__PAYLOAD,
		const PAYLOAD_TYPE* SOURCE_PAYLOAD
	) {
		if (NBT19133::__priv_chech_TagPayloadRead<PAYLOAD_TYPE>(TARGET__PAYLOAD)	&&	//���Ҫ���Ƶ��Ķ����Ƿ�Ϸ�
			SOURCE_PAYLOAD																//��������ƵĶ����Ƿ����
			) {																			//	|
			return true;																//	|_ true		���� true
		}																				//	|
		return false;																	//	|_ false
	}


	class TagBase {
	protected:
		//��ǩ����
		__PRIV_TYPE_TAG_NAME tagName;
		//��ǩID
		const __PRIV_TYPE_TAG_ID tagID;
		
	public:
		TagBase(
			const __PRIV_TYPE_TAG_ID SOURCE__TAG_ID,
			const __PRIV_TYPE_TAG_NAME SOURCE__TAG_NAME
		);
		TagBase(const __PRIV_TYPE_TAG_ID SOURCE__TAG_ID);
		TagBase(const TagBase& SOURCE__TAG);
		~TagBase();

	public:
		//����
		TagBase& operator=(const TagBase& SOURCE__TAG);
		//����Ƿ���ͬ
		bool operator==(const TagBase& SOURCE__TAG)const;
		/*���ñ�ǩ����
		* �βΣ�
		* SOURCE__TAG_NAME		Ҫ���õı�ǩ����
		* ���أ�
		* bool					���óɹ� true��ʧ�� false
		*/
		bool setTag_Name(const __PRIV_TYPE_TAG_NAME& SOURCE__TAG_NAME);
		/*��ȡ��ǩ����
		* �βΣ�
		* targetTagName			Ҫ���Ƶ��Ķ���
		* ���أ�
		* bool					��ȡ�ɹ� true��ʧ�� false
		*/
		bool getTag_Name(__PRIV_TYPE_TAG_NAME& targetTagName)const;
		/*��ȡ��ǩID
		* ���أ�
		* uint8_t				���ش����д洢�ı�ǩID
		*/
		__PRIV_TYPE_TAG_ID getTag_ID(void)const;
		/*����ǩ�����Ƿ�Ϊ��
		* ���أ�
		* bool					Ϊ�շ��� true�����򷵻� false
		*/
		bool emptyTag_Name(void)const;
		//�����ǩ����
		void clearTag_Name(void);
	};

	template<typename PAYLOAD_TYPE>
	class Tag:public TagBase {
	private:
		//����
		PAYLOAD_TYPE* payload;
	private:
		inline void __priv_ptr_PayloadPtrDel(void) {
			if (payload) { delete payload; }
			payload = nullptr;
			return;
		}

		inline bool __priv_ptr_PayloadPtrSet(const PAYLOAD_TYPE& SOURCE__PAYLOAD) {
			if (!NBT19133::__priv_check_TagPayloadCopy(SOURCE__PAYLOAD)) { return false; }	//���Դ�����Ƿ����

			this->__priv_ptr_PayloadPtrDel();												//����ָ��

			try { this->payload = new PAYLOAD_TYPE; }										//��ȡ�ռ�
			catch (std::bad_alloc e) {														//��ȡ�ռ�ʧ�ܴ�������
				throw NBT19133::NBT19133_ErrorType(											//	|_ Error��Ϣ
					"Tag",																	//	:
					"inline bool NBT19133::Tag::__priv_ptr_PayloadPtrSet(const PAYLOAD_TYPE& SOURCE__PAYLOAD)",
					"SOURCE__PAYLOAD = new PAYLOAD_TYPE throw bad_alloc"					//	:
				);																			//	|
				this->payload = nullptr;													//	|  ptr�ÿ�
				return false;																//	|  ����false
			}																				//	|
																							//	|
			*(this->payload) = SOURCE__PAYLOAD;												//	|_ ��ȡ�ɹ�����ֵ
			return true;																	//	|  ����true
		}

	public:
		bool setPayload_add(const PAYLOAD_TYPE& SOURCE__PAYLOAD) {
			return this->__priv_ptr_PayloadPtrSet(SOURCE__PAYLOAD);
		}

	};
}