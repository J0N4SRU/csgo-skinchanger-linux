#pragma once

#define VCLIENTENTITYLIST_INTERFACE_VERSION "VClientEntityList003"

class IClientEntity;

class IClientEntityList {
	public:
		IClientEntity* GetClientEntity(int index) {
			return GetVirtualFunction<IClientEntity*(*)(void*, int)>(this, 3)(this, index);
		}

		IClientEntity* GetClientEntityFromHandle(void* handle) {
			return GetVirtualFunction<IClientEntity*(*)(void*, void*)>(this, 4)(this, handle);
		}

		int GetHighestEntityIndex() {
			return GetVirtualFunction<int(*)(void*)>(this, 6)(this);
		}
};

extern IClientEntityList* entitylist;
