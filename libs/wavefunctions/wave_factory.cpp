/*
  QSTEM - image simulation for TEM/STEM/CBED
  Copyright (C) 2000-2010  Christoph Koch
  Copyright (C) 2010-2013  Christoph Koch, Michael Sarahan

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "wave_factory.hpp"

#include "wave_convergent.hpp"
#include "wave_plane.hpp"

namespace QSTEM
{

CWaveFactory::CWaveFactory()
{
	Register(1,    &CConvergentWave::Create);
	Register(2,    &CPlaneWave::Create);
}

CWaveFactory *CWaveFactory::Get()
{
	static CWaveFactory instance;
	return &instance;
}

void CWaveFactory::Register(const int type, CreateWaveFn pfnCreate)
{
	m_FactoryMap[type] = pfnCreate;
}

WavePtr CWaveFactory::GetWave(const int type, const ConfigPtr c)
{
	FactoryMap::iterator it = m_FactoryMap.find(type);
	if( it != m_FactoryMap.end() )
		return it->second(c);
	return WavePtr();
}

}
