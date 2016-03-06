#include <forward_list>
int gi;
void *address;

void * buildCode() {
	char *code = (char *)malloc(16);
	char *pMov = code;
	char *pJmp = code + 10;
	char *pAddress;
	pMov[0] = 0xc7;
	pMov[1] = 0x05;
	pAddress = pMov + 2;
	*((int *)pAddress) = (int)&gi;
	*((int *)(pAddress + 4)) = 18;
	pJmp[0] = 0xff;
	pJmp[1] = 0x25;
	*((int *)(&pJmp[2])) = (int)&address;
	return code;
}

void main() {
	void *code = buildCode();
	_asm {
		mov address, offset _lb1
	}

	gi = 12;
	printf("gi = %d\n", gi);
	_asm jmp code
	gi = 13;

_lb1:
	printf("gi = %d\n", gi);
	getchar();
}
