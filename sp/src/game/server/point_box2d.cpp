//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "igamesystem.h"
#include "point_box2d.h"


// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

LINK_ENTITY_TO_CLASS(logic_box2d, CPointBox2D);

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
CPointBox2D::~CPointBox2D()
{
	delete world;
	world = NULL;
}

CPointBox2D::CPointBox2D()
{
	
	// world
	{
		gravity_vec = b2Vec2(0.0f, -9.8f);
		world = new b2World(gravity_vec);
	}

	// ground
	{
		ground_body_def.position.Set(0.0f, -10.0f);
		ground_body = world->CreateBody(&ground_body_def);

		b2PolygonShape ground_box;
		ground_box.SetAsBox(50.0f, 10.0f);
		ground_body->CreateFixture(&ground_box, 0.0f);
	}

	// dynamic body
	{
		dynamic_body_def.type = b2_dynamicBody;
		dynamic_body_def.position.Set(0.0f, 4.0f);
		dynamic_body = world->CreateBody(&dynamic_body_def);

		b2PolygonShape dynamic_box;
		dynamic_box.SetAsBox(1.0f, 1.0f);

		b2FixtureDef fixture_def;
		fixture_def.shape = &dynamic_box;
		fixture_def.density = 1.0f;
		fixture_def.friction = 0.3f;

		dynamic_body->CreateFixture( &fixture_def );
	}
}

void CPointBox2D::Spawn()
{
	BaseClass::Spawn();

	m_IsOn = false;
}

int CPointBox2D::UpdateTransmitState(void)
{
	return SetTransmitState(FL_EDICT_ALWAYS);
}


void CPointBox2D::Think()
{
	Physics();
}

void CPointBox2D::Physics()
{
	// update box2d !!!!
	world->Step(TICK_INTERVAL, velocity_iterations, position_iterations);

	// get dynamic body position and angle
	b2Vec2 position = dynamic_body->GetPosition();
	float angle = dynamic_body->GetAngle();
	

	// debug draw
	// dynamic box
	Vector origin = Vector(position.x, position.y, 0);
	Vector mins = origin - Vector(1, 1, 0.1) * 2;
	Vector maxs = origin + Vector(1, 1, 0.1) * 2;
	QAngle orientation = QAngle(0, RAD2DEG(angle), 0);
	debugoverlay->AddBoxOverlay(origin, mins, maxs, orientation, 255, 255, 255, 200, TICK_INTERVAL * 2);
	Msg("origin: %4.2f %4.2f %4.2f || mins: %4.2f %4.2f %4.2f || maxs: %4.2f %4.2f %4.2f || orient: %4.2f %4.2f %4.2f\n", origin.x, origin.y, origin.z, mins.x, mins.y, mins.z, maxs.x, maxs.y, maxs.z, orientation.x, orientation.y, orientation.z);

	// ground
	debugoverlay->AddBoxOverlay(Vector(0, -10, 0), Vector(0, -10, 0) - Vector(50, 10, 0.1) * 2, Vector(0, -10, 0) + Vector(50, 10, 0.1) * 2, QAngle(0, 0, 0), 64, 255, 64, 200, TICK_INTERVAL * 2);

	// debug console
	Msg("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	Msg("---");

	// end
	SetNextThink(gpGlobals->curtime + TICK_INTERVAL );
}

// note!
// addboxoverlay doesnt rotate locally
// but wow holy shit it works !

void CPointBox2D::InputDebugFiddle(inputdata_t &inputdata)
{
	//dynamic_body->ApplyForce(b2Vec2(RandomFloat() * force_mul, RandomFloat() * force_mul), b2Vec2(RandomFloat() * 2, RandomFloat() * 2), true);
	dynamic_body->ApplyTorque(1000.0f, true);
	Msg("DebugFidle'd\n");
}

void CPointBox2D::InputSimulationOn(inputdata_t &inputdata)
{
	m_IsOn = true;
	SetNextThink(gpGlobals->curtime);
	m_OnSomething.FireOutput(this, this); // debug
}

void CPointBox2D::InputSimulationOff(inputdata_t &inputdata)
{
	m_IsOn = false;
	SetNextThink( TICK_NEVER_THINK );
	m_OnSomething.FireOutput(this, this); // debug
}


//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------

BEGIN_DATADESC(CPointBox2D)

// Save/restore Keyvalue fields
DEFINE_KEYFIELD(m_IsOn, FIELD_INTEGER, "is_on"),


// Input
DEFINE_INPUTFUNC(FIELD_VOID, "SimulationOn", InputSimulationOn),
DEFINE_INPUTFUNC(FIELD_VOID, "SimulationOff", InputSimulationOff),
DEFINE_INPUTFUNC(FIELD_VOID, "DebugFiddle", InputDebugFiddle),

// Output
DEFINE_OUTPUT(m_OnSomething, "OnSomething"),
END_DATADESC()

IMPLEMENT_SERVERCLASS_ST(CPointBox2D, DT_PointBox2D)

SendPropInt(SENDINFO(m_IsOn), 0, SPROP_NOSCALE),

END_SEND_TABLE()
