//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef CAMERA_H
#define CAMERA_H
#ifdef _WIN32
#pragma once
#endif

#include "cbase.h"

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------


#define _COMPOSITE_IMAGE_SIZE 1024
#define _COMPOSITE_PAGES 32

class CPointTimeloop : public CBaseEntity
{
public:
	DECLARE_CLASS(CPointTimeloop, CBaseEntity);
	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();
	CPointTimeloop();
	~CPointTimeloop();

	int  UpdateTransmitState(void);

	void Spawn(void);
	void Think();
	void DoSnapshot();


	void InputStart (inputdata_t &inputdata );
	void InputStop( inputdata_t &inputdata );
	void InputPause( inputdata_t &inputdata );
	void InputResume(inputdata_t &inputdata);
	void InputReset( inputdata_t &inputdata );

	CNetworkVar(int, m_ReplayWidth);
	CNetworkVar(int, m_ReplayHeight);
	CNetworkVar(int, m_Frame);
	CNetworkVar(int, m_FramesCount);
	CNetworkVar(int, m_Page);
	CNetworkVar(int, m_PagesCount);
	CNetworkVar(float, m_SnapshotDelay);
	CNetworkVar(float, m_Duration);
	CNetworkVar(int, m_IsOn);

	bool IsActive() { return m_IsOn == 1; }

	COutputEvent m_OnFinish;		// Fired when timeloop ends

private:
	void Init();
};


#endif // CAMERA_H
