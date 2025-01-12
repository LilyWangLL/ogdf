/** \file
 * \brief Contains constructive and improvement compaction by
 *        applying computation of longest paths in constraint graphs
 *
 * \author Carsten Gutwenger
 *
 * \par License:
 * This file is part of the Open Graph Drawing Framework (OGDF).
 *
 * \par
 * Copyright (C)<br>
 * See README.md in the OGDF root directory for details.
 *
 * \par
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * Version 2 or 3 as published by the Free Software Foundation;
 * see the file LICENSE.txt included in the packaging of this file
 * for details.
 *
 * \par
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * \par
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, see
 * http://www.gnu.org/copyleft/gpl.html
 */

#pragma once

#include <ogdf/basic/Graph.h>
#include <ogdf/basic/SList.h>
#include <ogdf/basic/basic.h>
#include <ogdf/orthogonal/internal/RoutingChannel.h>

namespace ogdf {

class GridLayoutMapped;
class OrthoRep;
class PlanRep;
template<class ATYPE>
class CompactionConstraintGraph;

/**
 * \brief Compaction algorithm using longest paths in the constraint graph.
 *
 * <h3>Optional Parameters</h3>
 *
 * <table>
 *   <tr>
 *     <th>Option</th><th>Type</th><th>Default</th><th>Description</th>
 *   </tr><tr>
 *     <td><i>tighten</i></td><td>bool</td><td>true</td>
 *     <td>if true, an additional improvement step tries to reduce the total edge length</td>
 *   </tr><tr>
 *     <td><i>max improvement steps</i></td><td>int</td><td>0</td>
 *     <td>the maximal number of steps performed by the improvement heuristic; 0 means no upper limit.</td>
 *   </tr>
 * </table>
 */
class OGDF_EXPORT LongestPathCompaction {
public:
	//! Creates an instance of the longest path compaction algorithm.
	explicit LongestPathCompaction(bool tighten = true, int maxImprovementSteps = 0);

	//! Constructive heurisitic for orthogonal representations.
	void constructiveHeuristics(PlanRep& PG, OrthoRep& OR, const RoutingChannel<int>& rc,
			GridLayoutMapped& drawing);


	//! Improvement heurisitic for orthogonal drawings.
	void improvementHeuristics(PlanRep& PG, OrthoRep& OR, const RoutingChannel<int>& rc,
			GridLayoutMapped& drawing);

	//
	// options

	//! Sets option <i>tighten</i> to \p select.
	void tighten(bool select) { m_tighten = select; }

	//! Returns the option <i>tighten</i>.
	bool tighten() const { return m_tighten; }

	//! Sets the option <i>max improvement steps</i>.
	void maxImprovementSteps(int maxSteps) { m_maxImprovementSteps = maxSteps; }

	//! Returns the option <i>max improvement steps</i>.
	int maxImprovementSteps() const { return m_maxImprovementSteps; }


private:
	void computeCoords(const CompactionConstraintGraph<int>& D, NodeArray<int>& pos);

	void applyLongestPaths(const CompactionConstraintGraph<int>& D, NodeArray<int>& pos);

	void moveComponents(const CompactionConstraintGraph<int>& D, NodeArray<int>& pos);


	// options
	bool m_tighten; //!< Tighten pseudo-components.
	int m_maxImprovementSteps; //!< The maximal number of improvement steps.

	SList<node> m_pseudoSources; //!< The list of pseudo-sources.
	NodeArray<int> m_component; //!< The pseudo component of a node.
};

}
