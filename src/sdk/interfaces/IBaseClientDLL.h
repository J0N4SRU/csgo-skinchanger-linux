#pragma once

#define CLIENT_DLL_INTERFACE_VERSION "VClient018"


enum DataUpdateType_t {
	DATA_UPDATE_CREATED = 0,
	DATA_UPDATE_DATATABLE_CHANGED,
};

class IClientNetworkable {
public:
	virtual ~IClientNetworkable() {};

	void PreDataUpdate(DataUpdateType_t updateType) {
		return GetVirtualFunction<void(*)(void*, DataUpdateType_t)>(this, 6)(this, updateType);
	}

};

typedef IClientNetworkable*	(*CreateClientClassFn)( int entnum, int serialNum );

struct ClientClass {
	CreateClientClassFn m_pCreateFn;
	void *m_pCreateEventFn;
	char *m_pNetworkName;
	void *m_pRecvTable;
	ClientClass *m_pNext;
	int m_ClassID;
};

class IBaseClientDLL {
	public:
		ClientClass* GetAllClasses() {
			return GetVirtualFunction<ClientClass*(*)(void*)>(this, 8)(this);
		}
};

extern IBaseClientDLL* clientdll;
