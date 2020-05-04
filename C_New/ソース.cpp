#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include <crtdbg.h>//VC Only.

//for local env C lang.

namespace Yakitori {
	template<class T>
	T* New(size_t N) {

		size_t S = N * sizeof(T);
		T* P = (T*)malloc(S);

		memset(P, 0, S);//oh cant set type of 64bit value... why int??

		return P;
	}
	template<class T>
	T* ReNew(T* OldMem,size_t N) {
		size_t S = N * sizeof(T);
		return (T*)realloc(OldMem, S);// need care the dungling pointer.
	}

	template<class T>
	void Free(T** Mem) {

		free(*Mem);
		*Mem = NULL;

		return;
	}

}

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//vc only

	size_t N = 16;

	int* P = Yakitori::New<int>(N);

	for (size_t i = 0; i < N; i++) {
		P[i] = i;

		printf("%d\n", P[i]);
	}

	int* P2 = Yakitori::ReNew(P,N*2);
	if (P2 == P) {
		P = NULL;
	}
	
	for (size_t i = 0; i < N*2; i++) {
		P2[i] = i;
		printf("%d\n", P2[i]);
	}

	Yakitori::Free(&P2);

	return 0;
}