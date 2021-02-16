//
// LinkControl - models Links that block radio transmissions
// Copyright (C) 2006 Christoph Sommer <christoph.sommer@informatik.uni-erlangen.de>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//


#ifndef LINK_LINK_H
#define LINK_LINK_H

#include <vector>
#include "veins/base/utils/Coord.h"
using namespace veins;

class Link {
	public:
		typedef std::vector<veins::Coord> Coords;

		Link();
		Link(const Link&);

		void setShape(Coords shape);
		const Coords& getShape() const;
		const veins::Coord getBboxP1() const;
		const veins::Coord getBboxP2() const;

		double getDistance(const veins::Coord * pos) const;

	protected:

		Coords coords;
		veins::Coord bboxP1;
		veins::Coord bboxP2;
};

#endif
