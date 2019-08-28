//////////////////////////////////////////////////////////////////////////////////////
// This file is distributed under the University of Illinois/NCSA Open Source License.
// See LICENSE file in top directory for details.
//
// Copyright (c) 2019 developers.
//
// File developed by: Peter Doak, doakpw@ornl.gov, Oak Ridge National Laboratory
//
// File refactored from VMC.h
//////////////////////////////////////////////////////////////////////////////////////

#ifndef QMCPLUSPLUS_CROWD_H
#define QMCPLUSPLUS_CROWD_H

#include <vector>
#include "Particle/MCPopulation.h"
#include "Estimators/EstimatorManagerBase.h"
#include "Estimators/EstimatorManagerCrowd.h"

namespace qmcplusplus
{
/** Driver synchronized step context
 * 
 *  assumed to live inside the drivers scope
 *  TODO: Construct and initialize in thread execution space
 */
class Crowd
{
public:
  using MCPWalker = MCPopulation::MCPWalker;
  /** This is the data structure for walkers within a crowd
   */
  Crowd(EstimatorManagerBase& emb) : estimator_manager_crowd_(emb) {}
  
  void startRun()
  {
    
  }

  void startBlock(int steps)
  {
    estimator_manager_crowd_.startBlock(steps);
  }

  void addWalker(MCPWalker& walker) { mcp_walkers_.push_back(walker); };

  auto
  beginWalkers() { return mcp_walkers_.begin(); }
  auto
  endWalkers() { return mcp_walkers_.end(); }

  int size() const { return mcp_walkers_.size(); }
private:
  std::vector<std::reference_wrapper<MCPWalker>> mcp_walkers_;
  EstimatorManagerCrowd estimator_manager_crowd_;
public:
};
} // namespace qmcplusplus
#endif
