#ifndef TNERENDERTARGETS_H_
#define TNERENDERTARGETS_H_
#ifdef _WIN32
#pragma once
#endif

#include "baseclientrendertargets.h" // Base class, with interfaces called by engine and inherited members to init common render   targets
#include "rendertexture.h"

// externs
class IMaterialSystem;
class IMaterialSystemHardwareConfig;

class CTNERenderTargets : public CBaseClientRenderTargets
{
	// no networked vars 
	DECLARE_CLASS_GAMEROOT(CTNERenderTargets, CBaseClientRenderTargets);
public:
	virtual void InitClientRenderTargets(IMaterialSystem* pMaterialSystem, IMaterialSystemHardwareConfig* pHardwareConfig);
	virtual void ShutdownClientRenderTargets();

	ITexture* CreateTimeloopReplayTexture(int which, IMaterialSystem* pMaterialSystem);

private:
	CTextureReference		m_TimeloopReplayTextures[MAX_TIMELOOP_REPLAY_TEXTURES];
};

extern CTNERenderTargets* TNERenderTargets;

#endif //TNERENDERTARGETS_H_