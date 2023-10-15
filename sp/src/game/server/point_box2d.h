//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef LOGIC_BOX2D_H
#define LOGIC_BOX2D_H
#ifdef _WIN32
#pragma once
#endif

#include "cbase.h"
#include "box2d/box2d.h"

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------


class CPointBox2D : public CBaseEntity
{
public:
	DECLARE_CLASS(CPointBox2D, CBaseEntity);
	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();
	CPointBox2D();
	~CPointBox2D();

	int UpdateTransmitState(void);

	void Spawn(void);
	void Think();
	void Physics();


	void InputSimulationOn(inputdata_t &inputdata);
	void InputSimulationOff(inputdata_t &inputdata);
	void InputDebugFiddle(inputdata_t &inputdata);

	CNetworkVar(int, m_IsOn);

	bool IsActive() { return m_IsOn == 1; }

	COutputEvent m_OnSomething;

private:
	int32 velocity_iterations = 8;
	int32 position_iterations = 3;

	b2World *world;
	b2Vec2 gravity_vec;

	b2BodyDef ground_body_def;
	b2Body* ground_body;

	b2BodyDef dynamic_body_def;
	b2Body* dynamic_body;
};

#endif // LOGIC_BOX2D_H