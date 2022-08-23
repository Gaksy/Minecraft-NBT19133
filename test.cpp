#include "NBT19133.h"

void testTagBase(void) {
	std::wstring tagName;
	tagName = L"NIHAO";

	NBT19133::TagBase TBtest(1);
	TBtest.setTag_Name(tagName);
	
	tagName.clear();
	if (TBtest.getTag_Name(tagName))
		wprintf(L"TBtest.getTag_Name : %s\n", tagName.c_str());
	else
		printf("ERROR!\n");

	NBT19133::TagBase TBtest0(TBtest);
	tagName.clear();
	if (TBtest0.getTag_Name(tagName))
		wprintf(L"TBtest0.getTag_Name : %s\n", tagName.c_str());
	else
		printf("ERROR!\n");

	printf("TBtest0.getTag_ID : %u\n", TBtest0.getTag_ID());

	printf("TagBase::operator== : %u", TBtest == TBtest0);

	return;
}

int main(void) {
	testTagBase();
	return 0;
}