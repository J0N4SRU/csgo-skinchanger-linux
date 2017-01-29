#pragma once

#define CLIENT_DLL_INTERFACE_VERSION "VClient018"


enum DataUpdateType_t
{
	DATA_UPDATE_CREATED = 0,
//	DATA_UPDATE_ENTERED_PVS,
	DATA_UPDATE_DATATABLE_CHANGED,
//	DATA_UPDATE_LEFT_PVS,
//	DATA_UPDATE_DESTROYED,
};

class IClientNetworkable
{
public:
	virtual ~IClientNetworkable() {};

	void PreDataUpdate(DataUpdateType_t updateType) {
		return GetVirtualFunction<void(*)(void*, DataUpdateType_t)>(this, 6)(this, updateType);
	}

};

struct RecvProp;

struct RecvTable
{
	RecvProp *m_pProps;
	int m_nProps;
	void *m_pDecoder;
	char *m_pNetTableName;
	bool m_bInitialized;
	bool m_bInMainList;
};

typedef IClientNetworkable*	(*CreateClientClassFn)( int entnum, int serialNum );

struct ClientClass
{
	CreateClientClassFn m_pCreateFn;
	void *m_pCreateEventFn;
	char *m_pNetworkName;
	RecvTable *m_pRecvTable;
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
