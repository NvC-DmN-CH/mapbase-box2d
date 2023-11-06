//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#include "cbase.h"
#include "c_point_timeloop.h"
#include "toolframework/itoolframework.h"
#include "toolframework_client.h"
#include "tier1/KeyValues.h"


// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

IMPLEMENT_CLIENTCLASS_DT(C_PointTimeloop, DT_PointTimeloop, CPointTimeloop)
	RecvPropInt(RECVINFO(m_ReplayWidth)),
	RecvPropInt(RECVINFO(m_ReplayHeight)),
	RecvPropInt(RECVINFO(m_Frame)),
	RecvPropInt(RECVINFO(m_FramesCount)),
	RecvPropInt(RECVINFO(m_Page)),
	RecvPropInt(RECVINFO(m_PagesCount)),
	RecvPropFloat(RECVINFO(m_SnapshotDelay)),
	RecvPropFloat(RECVINFO(m_Duration)),
	RecvPropInt(RECVINFO(m_isOn)),
END_RECV_TABLE()

C_PointTimeloop* g_TimeloopEntity;

C_PointTimeloop* GetTimeloopEntity()
{
	return g_TimeloopEntity;
}



C_PointTimeloop::C_PointTimeloop( void )
{
	if ( g_TimeloopEntity != NULL)
	{
		Warning("Multiple point_timeloop detected !!! \n");
	}

	g_TimeloopEntity = this;

//	Msg("POINT TIME LOOP CONSTRUCTOR !!!!!!");
}

C_PointTimeloop::~C_PointTimeloop( void )
{
	g_TimeloopEntity = NULL;
}