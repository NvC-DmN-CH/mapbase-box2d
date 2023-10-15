//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef C_LOGIC_BOX2D_H
#define C_LOGIC_BOX2D_H
#ifdef _WIN32
#pragma once
#endif

#include "c_baseentity.h"
#include "basetypes.h"

class C_PointBox2D : public C_BaseEntity
{
public:
	DECLARE_CLASS(C_PointBox2D, C_BaseEntity);
	DECLARE_CLIENTCLASS();

public:
	C_PointBox2D();
	~C_PointBox2D();

	int m_isOn;

private:
};

C_PointBox2D *GetBox2DManagerEntity();

#endif // C_LOGIC_BOX2D_H
