#include "../hooks.h"

void hkFrameStageNotify(void* thisptr, ClientFrameStage_t stage) {
	/* perform replacements during postdataupdate */
	while (stage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START) {
		/* get our player entity */
		int localplayer_idx = engine->GetLocalPlayer();
		C_BasePlayer* localplayer = reinterpret_cast<C_BasePlayer*>(entitylist->GetClientEntity(localplayer_idx));

		if (!localplayer || localplayer->GetLifeState() != LIFE_ALIVE)
			break;

		/* get information about our player */
		player_info_t localplayer_info;

		if (!engine->GetPlayerInfo(localplayer_idx, &localplayer_info))
			break;

		/* get a list of weapon we're holding */
		int* weapons = localplayer->GetWeapons();

		if (!weapons)
			break;

		for (int i = 0; i < 64; i++) {
			/* check if the handle is invalid */
			if (weapons[i] == -1)
				continue;

			C_BaseAttributableItem* weapon = reinterpret_cast<C_BaseAttributableItem*>(entitylist->GetClientEntity(weapons[i] & 0xFFF));

			/* check if the weapon pointer is invalid */
			if (!weapon)
				continue;

			switch (*weapon->GetItemDefinitionIndex()) {
				/* AWP | Dragon Lore */
				case WEAPON_AWP:
					*weapon->GetFallbackPaintKit() = 344; break;

				/* AK-47 | Redline */
				case WEAPON_AK47:
					*weapon->GetFallbackPaintKit() = 282; break;

				/* M4A4 | Howl */
				case WEAPON_M4A1:
					*weapon->GetFallbackPaintKit() = 309; break;

				/* Desert Eagle | Conspiracy */
				case WEAPON_DEAGLE:
					*weapon->GetFallbackPaintKit() = 351; break;

				/* Glock-18 | Fade */
				case WEAPON_GLOCK:
					*weapon->GetFallbackPaintKit() = 38; break;

				/* USP-S | Stainless */
				case WEAPON_USP_SILENCER:
					*weapon->GetFallbackPaintKit() = 277; break;

				/* Karambit | Tiger Tooth */
				case WEAPON_KNIFE:
					*weapon->GetItemDefinitionIndex() = WEAPON_KNIFE_KARAMBIT;
					*weapon->GetModelIndex() = modelinfo->GetModelIndex("models/weapons/v_knife_karam.mdl");
					*weapon->GetFallbackPaintKit() = 409; break;

				/* M9 Bayonet | Crimson Web */
				case WEAPON_KNIFE_T:
					*weapon->GetItemDefinitionIndex() = WEAPON_KNIFE_M9_BAYONET;
					*weapon->GetModelIndex() = modelinfo->GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
					*weapon->GetFallbackPaintKit() = 12; break;
			}

			/* write to weapon name tag */
			snprintf(weapon->GetCustomName(), 32, "%s", "chameleon-x64 // aixxe.net");

			/* remove all wear */
			*weapon->GetFallbackWear() = 0.f;

			/* use stattrak on everything */
			*weapon->GetEntityQuality() = 9;
			*weapon->GetFallbackStatTrak() = 133337;
			*weapon->GetAccountID() = localplayer_info.xuidlow;

			/* force our fallback values to be used */
			*weapon->GetItemIDHigh() = -1;
		}

		/* get the viewmodel entity from our local player */
		int viewmodel_entindex = localplayer->GetViewModel() & 0xFFF;
		C_BaseViewModel* viewmodel = reinterpret_cast<C_BaseViewModel*>(entitylist->GetClientEntity(viewmodel_entindex));

		if (!viewmodel)
			break;

		/* get the weapon entity this viewmodel corresponds to */
		int weapon_entindex = viewmodel->GetWeapon() & 0xFFF;
		C_BaseCombatWeapon* active_weapon = reinterpret_cast<C_BaseCombatWeapon*>(entitylist->GetClientEntity(weapon_entindex));

		if (!active_weapon)
			break;

		switch (*active_weapon->GetItemDefinitionIndex()) {
			case WEAPON_KNIFE_KARAMBIT:
				*viewmodel->GetModelIndex() = modelinfo->GetModelIndex("models/weapons/v_knife_karam.mdl"); break;
			case WEAPON_KNIFE_M9_BAYONET:
				*viewmodel->GetModelIndex() = modelinfo->GetModelIndex("models/weapons/v_knife_m9_bay.mdl"); break;
		}

		break;
	}

	/* call original function after we've made our changes */
	return clientdll_hook->GetOriginalFunction<FrameStageNotifyFn>(36)(thisptr, stage);
}