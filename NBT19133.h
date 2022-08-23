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
		if (&SOURCE__TAG_NAME							&&	//检查标签名称是否可用
			!SOURCE__TAG_NAME.empty()					&&	//检查标签名称是否为空
			SOURCE__TAG_NAME.size() <= MAXSIZE_TAGNAME		//检查标签名称的大小是否超过限制
			) {												//	|	&&
			return true;									//	|_ true		返回 true
		}													//	|
		return false;										//	|_ false	返回 false
	}
	inline bool __priv_check_TagNameRead(const __PRIV_TYPE_TAG_NAME& TARGET__TAG_NAME) {
		if (&TARGET__TAG_NAME			&&					//检查要复制到的对象是否可用
			TARGET__TAG_NAME.empty()						//检查要复制到的对象是否是空的
			) {												//	|	&&
			return true;									//	|_ true		返回 true
		}													//	|
		return false;										//	|_ false	返回 false
	}
	inline bool __priv_check_TagNameRead(
		const __PRIV_TYPE_TAG_NAME& TARGET__TAG_NAME,
		const __PRIV_TYPE_TAG_NAME& SOURCE__TAG_NAME
	) {
		if (NBT19133::__priv_check_TagNameCopy(SOURCE__TAG_NAME) &&	//检查被复制的对象是否可用
			NBT19133::__priv_check_TagNameRead(TARGET__TAG_NAME)	//检查复制到的对象是否可用
			) {														//	|	&&
			return true;											//	|_ true		返回 true
		}															//	|
		return false;												//	|_ false	返回 false
	}

	template<typename PAYLOAD_TYPE>
	inline bool __priv_check_TagPayloadCopy(const PAYLOAD_TYPE& SOURCE__PAYLOAD) {
		if (&SOURCE__PAYLOAD) { return true; }											//检查要复制的对象是否可用
		return false;
	}
	template<typename PAYLOAD_TYPE>
	inline bool __priv_chech_TagPayloadRead(const PAYLOAD_TYPE& TARGET_PAYLOAD) {
		if (&TARGET_PAYLOAD) { return true; }											//检查要复制到的对象是否可用
		return false;
	}
	template<typename PAYLOAD_TYPE>
	inline bool __priv_check_TagPayloadRead(
		const PAYLOAD_TYPE& TARGET__PAYLOAD,
		const PAYLOAD_TYPE* SOURCE_PAYLOAD
	) {
		if (NBT19133::__priv_chech_TagPayloadRead<PAYLOAD_TYPE>(TARGET__PAYLOAD)	&&	//检查要复制到的对象是否合法
			SOURCE_PAYLOAD																//检擦被复制的对象是否可用
			) {																			//	|
			return true;																//	|_ true		返回 true
		}																				//	|
		return false;																	//	|_ false
	}


	class TagBase {
	protected:
		//标签名称
		__PRIV_TYPE_TAG_NAME tagName;
		//标签ID
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
		//拷贝
		TagBase& operator=(const TagBase& SOURCE__TAG);
		//检查是否相同
		bool operator==(const TagBase& SOURCE__TAG)const;
		/*设置标签名称
		* 形参：
		* SOURCE__TAG_NAME		要设置的标签名称
		* 返回：
		* bool					设置成功 true，失败 false
		*/
		bool setTag_Name(const __PRIV_TYPE_TAG_NAME& SOURCE__TAG_NAME);
		/*获取标签名称
		* 形参：
		* targetTagName			要复制到的对象
		* 返回：
		* bool					获取成功 true，失败 false
		*/
		bool getTag_Name(__PRIV_TYPE_TAG_NAME& targetTagName)const;
		/*获取标签ID
		* 返回：
		* uint8_t				返回此类中存储的标签ID
		*/
		__PRIV_TYPE_TAG_ID getTag_ID(void)const;
		/*检查标签名称是否为空
		* 返回：
		* bool					为空返回 true，否则返回 false
		*/
		bool emptyTag_Name(void)const;
		//清除标签名称
		void clearTag_Name(void);
	};

	template<typename PAYLOAD_TYPE>
	class Tag:public TagBase {
	private:
		//负载
		PAYLOAD_TYPE* payload;
	private:
		inline void __priv_ptr_PayloadPtrDel(void) {
			if (payload) { delete payload; }
			payload = nullptr;
			return;
		}

		inline bool __priv_ptr_PayloadPtrSet(const PAYLOAD_TYPE& SOURCE__PAYLOAD) {
			if (!NBT19133::__priv_check_TagPayloadCopy(SOURCE__PAYLOAD)) { return false; }	//检查源负载是否可用

			this->__priv_ptr_PayloadPtrDel();												//清理指针

			try { this->payload = new PAYLOAD_TYPE; }										//获取空间
			catch (std::bad_alloc e) {														//获取空间失败处理流程
				throw NBT19133::NBT19133_ErrorType(											//	|_ Error信息
					"Tag",																	//	:
					"inline bool NBT19133::Tag::__priv_ptr_PayloadPtrSet(const PAYLOAD_TYPE& SOURCE__PAYLOAD)",
					"SOURCE__PAYLOAD = new PAYLOAD_TYPE throw bad_alloc"					//	:
				);																			//	|
				this->payload = nullptr;													//	|  ptr置空
				return false;																//	|  返回false
			}																				//	|
																							//	|
			*(this->payload) = SOURCE__PAYLOAD;												//	|_ 获取成功，赋值
			return true;																	//	|  返回true
		}

	public:
		bool setPayload_add(const PAYLOAD_TYPE& SOURCE__PAYLOAD) {
			return this->__priv_ptr_PayloadPtrSet(SOURCE__PAYLOAD);
		}

	};
}