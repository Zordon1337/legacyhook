#pragma once
#include "Recv.h"
#include "memory.h"
class ClientClass {
private:
	char __pad[0x8];
public:
	char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int m_ClassID;
};

class IBaseClientDLL {
public:
	inline ClientClass* GetAllClasses() {
		return memory::Call<ClientClass*>(this, 8);
	}
};