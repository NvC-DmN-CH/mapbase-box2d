#include "cbase.h"
#include "tne_RenderTargets.h"
#include "materialsystem\imaterialsystem.h"
#include "rendertexture.h"

ITexture* CTNERenderTargets::CreateTimeloopReplayTexture(int which, IMaterialSystem* pMaterialSystem)
{
	char szName[32];
	Q_snprintf(szName, sizeof(szName), "_rt_TimeloopReplay%i", which);

	Msg("Creating Replay Render Target: %s \n", szName);

	return pMaterialSystem->CreateNamedRenderTargetTexture(
		szName,
		1024, 1024, RT_SIZE_OFFSCREEN,
		IMAGE_FORMAT_RGB888,
		MATERIAL_RT_DEPTH_NONE,
		TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT,
		false);

}

//-----------------------------------------------------------------------------
// Purpose: Called by the engine in material system init and shutdown.
//			Clients should override this in their inherited version, but the base
//			is to init all standard render targets for use.
// Input  : pMaterialSystem - the engine's material system (our singleton is not yet inited at the time this is called)
//			pHardwareConfig - the user hardware config, useful for conditional render target setup
//-----------------------------------------------------------------------------
void CTNERenderTargets::InitClientRenderTargets(IMaterialSystem* pMaterialSystem, IMaterialSystemHardwareConfig* pHardwareConfig)
{
	for (int i = 0; i < MAX_TIMELOOP_REPLAY_TEXTURES; i++)
	{
		m_TimeloopReplayTextures[i].Init( CreateTimeloopReplayTexture(i, pMaterialSystem) );
	}

	// Water effects & camera from the base class (standard HL2 targets) 
	BaseClass::InitClientRenderTargets(pMaterialSystem, pHardwareConfig);
}

//-----------------------------------------------------------------------------
// Purpose: Shut down each CTextureReference we created in InitClientRenderTargets.
//			Called by the engine in material system shutdown.
// Input  :  - 
//-----------------------------------------------------------------------------
void CTNERenderTargets::ShutdownClientRenderTargets()
{
	for (int i = 0; i < MAX_TIMELOOP_REPLAY_TEXTURES; i++)
	{
		m_TimeloopReplayTextures[i].Shutdown();
	}


	// Clean up standard HL2 RTs (camera and water) 
	BaseClass::ShutdownClientRenderTargets();
}

//add the interface!
static CTNERenderTargets g_TNERenderTargets;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CTNERenderTargets, IClientRenderTargets, CLIENTRENDERTARGETS_INTERFACE_VERSION, g_TNERenderTargets);
CTNERenderTargets* TNERenderTargets = &g_TNERenderTargets;