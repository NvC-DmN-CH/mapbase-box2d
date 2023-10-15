//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#include "cbase.h"
#include "c_point_box2d.h"
#include "toolframework/itoolframework.h"
#include "toolframework_client.h"
#include "tier1/KeyValues.h"


// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

IMPLEMENT_CLIENTCLASS_DT(C_PointBox2D, DT_PointBox2D, CPointBox2D)
RecvPropInt(RECVINFO(m_isOn)),
END_RECV_TABLE()

C_PointBox2D* g_Box2DManagerEntity;

C_PointBox2D* GetBox2DManagerEntity()
{
	return g_Box2DManagerEntity;
}


C_PointBox2D::C_PointBox2D(void)
{
	if (g_Box2DManagerEntity != NULL)
	{
		Warning("Multiple box2d manager entities detected !!! \n");
	}

	g_Box2DManagerEntity = this;

	//	Msg("POINT TIME LOOP CONSTRUCTOR !!!!!!");
}

C_PointBox2D::~C_PointBox2D(void)
{
	g_Box2DManagerEntity = NULL;
}