//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef C_POINTTIMELOOP_H
#define C_POINTTIMELOOP_H
#ifdef _WIN32
#pragma once
#endif

#include "c_baseentity.h"
#include "basetypes.h"

class C_PointTimeloop : public C_BaseEntity
{
public:
	DECLARE_CLASS(C_PointTimeloop, C_BaseEntity);
	DECLARE_CLIENTCLASS();

public:
	C_PointTimeloop();
	~C_PointTimeloop();


	int m_ReplayWidth;
	int m_ReplayHeight;
	int m_Frame;
	int m_FramesCount;
	int m_Page;
	int m_PagesCount;
	float m_LastSnapshot;
	float m_SnapshotDelay;
	float m_Duration;
	int m_isOn;

	int m_FramePrevious = -1;

private:
};

C_PointTimeloop *GetTimeloopEntity();

#endif // C_POINTTIMELOOP_H
