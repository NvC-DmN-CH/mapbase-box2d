//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "igamesystem.h"
#include "point_timeloop.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

LINK_ENTITY_TO_CLASS(logic_timeloop, CPointTimeloop);

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
CPointTimeloop::~CPointTimeloop()
{

}

CPointTimeloop::CPointTimeloop()
{

}

void CPointTimeloop::Spawn()
{
	BaseClass::Spawn();

	Init();

	m_FramesCount = (_COMPOSITE_IMAGE_SIZE / m_ReplayWidth) * (_COMPOSITE_IMAGE_SIZE / m_ReplayHeight);
	m_PagesCount = _COMPOSITE_PAGES;
	m_SnapshotDelay = m_Duration / (float)(m_FramesCount * m_PagesCount);
}

int CPointTimeloop::UpdateTransmitState(void)
{
	return SetTransmitState( FL_EDICT_ALWAYS );
}


void CPointTimeloop::Think()
{
	if ( m_IsOn )
	{
		DoSnapshot();
	}
}

void CPointTimeloop::DoSnapshot()
{
	m_Frame++;

	if (m_Frame >= m_FramesCount)
	{
		m_Page++;

		if (m_Page >= m_PagesCount)
		{
			m_IsOn = false;
			m_Frame = m_FramesCount - 1;
			m_Page = m_PagesCount - 1;
			m_OnFinish.FireOutput(this, this);
			return;
		}
	}

	m_Frame = m_Frame % m_FramesCount;


	SetNextThink(gpGlobals->curtime + m_SnapshotDelay);
}


void CPointTimeloop::InputStart(inputdata_t &inputdata)
{
	m_IsOn = true;
	SetNextThink(gpGlobals->curtime + m_SnapshotDelay);
}

void CPointTimeloop::InputStop(inputdata_t &inputdata)
{
	m_IsOn = false;
	m_OnFinish.FireOutput(this, this);
}


void CPointTimeloop::InputPause(inputdata_t &inputdata)
{
	m_IsOn = false;
}

void CPointTimeloop::InputResume(inputdata_t &inputdata)
{
	m_IsOn = true;
	SetNextThink(gpGlobals->curtime + m_SnapshotDelay);
}

void CPointTimeloop::InputReset(inputdata_t &inputdata)
{
	Init();
}

void CPointTimeloop::Init()
{
	m_IsOn = false;
	m_Frame = -1;
	m_Page = 0;
}


//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------

BEGIN_DATADESC(CPointTimeloop)

// Save/restore Keyvalue fields
DEFINE_KEYFIELD(m_ReplayWidth, FIELD_INTEGER, "replay_width"),
DEFINE_KEYFIELD(m_ReplayHeight, FIELD_INTEGER, "replay_height"),
DEFINE_KEYFIELD(m_Duration, FIELD_FLOAT, "duration"),

DEFINE_KEYFIELD(m_Frame, FIELD_INTEGER, "frame"),
DEFINE_KEYFIELD(m_FramesCount, FIELD_INTEGER, "frames_count"),
DEFINE_KEYFIELD(m_Page, FIELD_INTEGER, "page"),
DEFINE_KEYFIELD(m_PagesCount, FIELD_INTEGER, "pages_count"),
DEFINE_KEYFIELD(m_SnapshotDelay, FIELD_FLOAT, "snapshot_delay"),
DEFINE_KEYFIELD(m_IsOn, FIELD_INTEGER, "is_on"),


// Input
DEFINE_INPUTFUNC(FIELD_VOID, "Start", InputStart),
DEFINE_INPUTFUNC(FIELD_VOID, "Stop", InputStop),
DEFINE_INPUTFUNC(FIELD_VOID, "Pause", InputPause),
DEFINE_INPUTFUNC(FIELD_VOID, "Resume", InputResume),
DEFINE_INPUTFUNC(FIELD_VOID, "Reset", InputReset),

// Output
DEFINE_OUTPUT(m_OnFinish, "OnFinish"),
END_DATADESC()

IMPLEMENT_SERVERCLASS_ST(CPointTimeloop, DT_PointTimeloop)

	SendPropInt(SENDINFO(m_ReplayWidth), 0, SPROP_NOSCALE),
	SendPropInt(SENDINFO(m_ReplayHeight), 0, SPROP_NOSCALE),
	SendPropFloat(SENDINFO(m_Duration), 0, SPROP_NOSCALE),

	SendPropInt(SENDINFO(m_Frame), 0, SPROP_NOSCALE),
	SendPropInt(SENDINFO(m_FramesCount), 0, SPROP_NOSCALE),
	SendPropInt(SENDINFO(m_Page), 0, SPROP_NOSCALE),
	SendPropInt(SENDINFO(m_PagesCount), 0, SPROP_NOSCALE),
	SendPropFloat(SENDINFO(m_SnapshotDelay), 0, SPROP_NOSCALE),
	SendPropInt(SENDINFO(m_IsOn), 0, SPROP_NOSCALE),

END_SEND_TABLE()
