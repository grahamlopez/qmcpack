//////////////////////////////////////////////////////////////////////////////////////
// This file is distributed under the University of Illinois/NCSA Open Source License.
// See LICENSE file in top directory for details.
//
// Copyright (c) 2016 Jeongnim Kim and QMCPACK developers.
//
// File developed by: Jeremy McMinnis, jmcminis@gmail.com, University of Illinois at Urbana-Champaign
//                    Jeongnim Kim, jeongnim.kim@gmail.com, University of Illinois at Urbana-Champaign
//                    Mark Dewing, markdewing@gmail.com, University of Illinois at Urbana-Champaign
//
// File created by: Jeongnim Kim, jeongnim.kim@gmail.com, University of Illinois at Urbana-Champaign
//////////////////////////////////////////////////////////////////////////////////////
    
    


/** @file ProgressReportEngine.h
 * @brief declaration of ProgressReportEngine
 */

#ifndef QMCPLUSPLUS_PROGRESSREPORTENGINE_H
#define QMCPLUSPLUS_PROGRESSREPORTENGINE_H

#include "Utilities/OhmmsInfo.h"
#include "Message/Communicate.h"
#include "Utilities/Timer.h"
#include "OhmmsData/OhmmsElementBase.h"

namespace qmcplusplus
{
/**
 *
 * Final class and should not be derived.
 */
class ReportEngine
{
public:

  inline ReportEngine(const std::string& cname, const std::string& fname, int atype=1):
    ReportType(atype),ClassName(cname), FuncName(fname), LogBuffer(*OhmmsInfo::Log)
  {
    if (DoOutput) {
      LogBuffer << "  " << ClassName << "::" << FuncName << "\n";
      // If there is structured output it should go to another file, not the stdout stream
      //if(ReportType)
      //  LogBuffer << ("<echo className=\""+ClassName+"\" funcName=\""+FuncName+"\">\n");
      //else
      //  LogBuffer << ("<"+ClassName+">\n");
      LogBuffer.flush(); //always flush
    }
  }

  inline ~ReportEngine()
  {
    //if(ReportType)
    //  LogBuffer << "</echo>\n";
    //else
    //  LogBuffer << ("</"+ClassName+">\n");
    LogBuffer.flush();
  }

  inline void flush()
  {
    if (DoOutput)
    {
      LogBuffer << '\n';
      LogBuffer.flush();
    }
  }

  inline void warning(const std::string& msg)
  {
    LogBuffer << ("WARNING: "+msg+"\n");
  }

  inline void error(const std::string& msg, bool fatal=false)
  {
    LogBuffer << ("ERROR: "+msg+"\n");
    if(fatal)
      APP_ABORT(ClassName+"::"+FuncName);
  }

  void echo(xmlNodePtr cur, bool recursive=false);

  static void enableOutput()
  {
    DoOutput = true;
  }

private:
  ///type of report
  int ReportType;
  /** class Name
   */
  std::string ClassName;
  /** name of the current  member function
   */
  std::string FuncName;
  /** arguments
   */
  std::vector<std::string> ArgList;
  /** stream for log message
   */
  OhmmsInform& LogBuffer;
  //disable copy constructor
  ReportEngine(const ReportEngine& a):LogBuffer(*OhmmsInfo::Log) {}

  static bool DoOutput;

};

// templated version of operator<< for Inform objects
template<class T>
inline
ReportEngine& operator<<(ReportEngine& o, const T& val)
{
  app_log()<< val;
  return o;
}
}
#endif // QMCPLUSPLUS_MPIOBJECTBASE_H
/***************************************************************************
 * $RCSfile$   $Author: jnkim $
 * $Revision: 2468 $   $Date: 2008-02-22 09:27:30 -0500 (Fri, 22 Feb 2008) $
 * $Id: Communicate.h 2468 2008-02-22 14:27:30Z jnkim $
 ***************************************************************************/
