/*=========================================================================

  Program:   CMake - Cross-Platform Makefile Generator
  Module:    $RCSfile$
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
  See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "cmCTest.h"
#include "cmake.h"
#include "cmMakefile.h"
#include "cmLocalGenerator.h"
#include "cmGlobalGenerator.h"
#include <cmsys/Directory.hxx>
#include "cmGlob.h"
#include "cmDynamicLoader.h"

#include "cmcTestScriptHandler.h"
#include "cmcTestUpdateHandler.h"
#include "cmcTestConfigureHandler.h"

#include "cmCTestSubmit.h"
#include "curl/curl.h"

#include <cmsys/RegularExpression.hxx>
#include <cmsys/Process.h>
#include <cmsys/Base64.h>

#include <stdlib.h> 
#include <time.h>
#include <math.h>
#include <float.h>

#include <memory> // auto_ptr

#define SAFEDIV(x,y) (((y)!=0)?((x)/(y)):(0))
#define DEBUGOUT std::cout << __LINE__ << " "; std::cout
#define DEBUGERR std::cerr << __LINE__ << " "; std::cerr

struct tm* cmCTest::GetNightlyTime(std::string str, 
                                          bool verbose, 
                                          bool tomorrowtag)
{
  struct tm* lctime;
  time_t tctime = time(0);
  if ( verbose )
    {
    std::cout << "Determine Nightly Start Time" << std::endl;
    std::cout << "   Specified time: " << str.c_str() << std::endl;
    }
  //Convert the nightly start time to seconds. Since we are
  //providing only a time and a timezone, the current date of
  //the local machine is assumed. Consequently, nightlySeconds
  //is the time at which the nightly dashboard was opened or
  //will be opened on the date of the current client machine.
  //As such, this time may be in the past or in the future.
  time_t ntime = curl_getdate(str.c_str(), &tctime);
  if ( verbose )
    {
    std::cout << "   Get curl time: " << ntime << std::endl;
    }
  tctime = time(0);
  if ( verbose )
    {
    std::cout << "   Get the current time: " << tctime << std::endl;
    }

  const int dayLength = 24 * 60 * 60;
  //std::cout << "Seconds: " << tctime << std::endl;
  if ( ntime > tctime )
    {
    // If nightlySeconds is in the past, this is the current
    // open dashboard, then return nightlySeconds.  If
    // nightlySeconds is in the future, this is the next
    // dashboard to be opened, so subtract 24 hours to get the
    // time of the current open dashboard
    ntime -= dayLength;
    //std::cout << "Pick yesterday" << std::endl;
    if ( verbose )
      {
      std::cout << "   Future time, subtract day: " << ntime << std::endl;
      }
    }
  if ( (tctime - ntime) >  dayLength )
    {
    ntime += dayLength;
    if ( verbose )
      {
      std::cout << "   Past time, subtract day: " << ntime << std::endl;
      }
    }
  //std::cout << "nightlySeconds: " << ntime << std::endl;
  if ( verbose )
    {
    std::cout << "   Current time: " << tctime
              << " Nightly time: " << ntime << std::endl;
    }
  if ( tomorrowtag )
    {
    std::cout << "Use future tag, Add a day" << std::endl;
    ntime += dayLength;
    }
  lctime = gmtime(&ntime);
  return lctime;
}

static std::string CleanString(const std::string& str)
{
  std::string::size_type spos = str.find_first_not_of(" \n\t\r\f\v");
  std::string::size_type epos = str.find_last_not_of(" \n\t\r\f\v");
  if ( spos == str.npos )
    {
    return std::string();
    }
  if ( epos != str.npos )
    {
    epos = epos - spos + 1;
    }
  return str.substr(spos, epos);
}

std::string cmCTest::CurrentTime()
{
  time_t currenttime = time(0);
  struct tm* t = localtime(&currenttime);
  //return ::CleanString(ctime(&currenttime));
  char current_time[1024];
  if ( m_ShortDateFormat )
    {
    strftime(current_time, 1000, "%b %d %H:%M %Z", t);
    }
  else
    {
    strftime(current_time, 1000, "%a %b %d %H:%M:%S %Z %Y", t);
    }
  //std::cout << "Current_Time: " << current_time << std::endl;
  return cmCTest::MakeXMLSafe(::CleanString(current_time));
}

static const char* cmCTestErrorMatches[] = {
  "^[Bb]us [Ee]rror",
  "^[Ss]egmentation [Vv]iolation",
  "^[Ss]egmentation [Ff]ault",
  "([^ :]+):([0-9]+): ([^ \\t])",
  "([^:]+): error[ \\t]*[0-9]+[ \\t]*:",
  "^Error ([0-9]+):",
  "^Fatal",
  "^Error: ",
  "^Error ",
  "[0-9] ERROR: ",
  "^\"[^\"]+\", line [0-9]+: [^Ww]",
  "^cc[^C]*CC: ERROR File = ([^,]+), Line = ([0-9]+)",
  "^ld([^:])*:([ \\t])*ERROR([^:])*:",
  "^ild:([ \\t])*\\(undefined symbol\\)",
  "([^ :]+) : (error|fatal error|catastrophic error)",
  "([^:]+): (Error:|error|undefined reference|multiply defined)",
  "([^:]+)\\(([^\\)]+)\\) : (error|fatal error|catastrophic error)",
  "^fatal error C[0-9]+:",
  ": syntax error ",
  "^collect2: ld returned 1 exit status",
  "Unsatisfied symbols:",
  "^Unresolved:",
  "Undefined symbols:",
  "^Undefined[ \\t]+first referenced",
  "^CMake Error:",
  ":[ \\t]cannot find",
  ":[ \\t]can't find",
  ": \\*\\*\\* No rule to make target \\`.*\\'.  Stop",
  ": Invalid loader fixup for symbol",
  ": internal link edit command failed",
  ": Unrecognized option \\`.*\\'",
  "\", line [0-9]+\\.[0-9]+: [0-9]+-[0-9]+ \\([^W]\\)",
  "ld: 0706-006 Cannot find or open library file: -l ",
  "ild: \\(argument error\\) can't find library argument ::",
  "^could not be found and will not be loaded.",
  "s:616 string too big",
  "make: Fatal error: ",
  "ld: 0711-993 Error occurred while writing to the output file:",
  "make: \\*\\*\\*.*Error",
  0
};

static const char* cmCTestErrorExceptions[] = {
  "instantiated from ",
  "candidates are:",
  ": warning",
  "makefile:",
  "Makefile:",
  ":[ \\t]+Where:",
  "([^ :]+):([0-9]+): Warning",
  0
};

static const char* cmCTestWarningMatches[] = {
  "([^ :]+):([0-9]+): warning:",
  "^cc[^C]*CC: WARNING File = ([^,]+), Line = ([0-9]+)",
  "^ld([^:])*:([ \\t])*WARNING([^:])*:",
  "([^:]+): warning ([0-9]+):",
  "^\"[^\"]+\", line [0-9]+: [Ww]arning",
  "([^:]+): warning[ \\t]*[0-9]+[ \\t]*:",
  "^Warning ([0-9]+):",
  "^Warning ",
  "WARNING: ",
  "([^ :]+) : warning",
  "([^:]+): warning",
  "\", line [0-9]+\\.[0-9]+: [0-9]+-[0-9]+ \\(W\\)",
  "^cxx: Warning:",
  ".*file: .* has no symbols",
  "([^ :]+):([0-9]+): Warning",
  0
};

static const char* cmCTestWarningExceptions[] = {
  "/usr/openwin/include/X11/Xlib\\.h:[0-9]+: warning: ANSI C\\+\\+ forbids declaration",
  "/usr/openwin/include/X11/Xutil\\.h:[0-9]+: warning: ANSI C\\+\\+ forbids declaration",
  "/usr/openwin/include/X11/XResource\\.h:[0-9]+: warning: ANSI C\\+\\+ forbids declaration",
  "WARNING 84 :",
  "WARNING 47 :",
  "makefile:",
  "Makefile:",
  "warning:  Clock skew detected.  Your build may be incomplete.",
  "/usr/openwin/include/GL/[^:]+:",
  "bind_at_load",
  "XrmQGetResource",
  "IceFlush",
  "warning LNK4089: all references to [^ \\t]+ discarded by .OPT:REF",
  "ld32: WARNING 85: definition of dataKey in",
  "cc: warning 422: Unknown option \"\\+b",
  "_with_warning_C",
  0
};

static const char* cmCTestMemCheckResultStrings[] = {
  "ABR",
  "ABW",
  "ABWL",
  "COR",
  "EXU",
  "FFM",
  "FIM",
  "FMM",
  "FMR",
  "FMW",
  "FUM",
  "IPR",
  "IPW",
  "MAF",
  "MLK",
  "MPK",
  "NPR",
  "ODS",
  "PAR",
  "PLK",
  "UMC",
  "UMR",
  0
};

static const char* cmCTestMemCheckResultLongStrings[] = {
  "Threading Problem",
  "ABW",
  "ABWL",
  "COR",
  "EXU",
  "FFM",
  "FIM",
  "Mismatched deallocation",
  "FMR",
  "FMW",
  "FUM",
  "IPR",
  "IPW",
  "MAF",
  "Memory Leak",
  "Potential Memory Leak",
  "NPR",
  "ODS",
  "Invalid syscall param",
  "PLK",
  "Uninitialized Memory Conditional",
  "Uninitialized Memory Read",
  0
};

std::string cmCTest::MakeXMLSafe(const std::string& str)
{
  cmOStringStream ost;
  // By uncommenting the lcnt code, it will put newline every 120 characters
  //int lcnt = 0;
  for (std::string::size_type  pos = 0; pos < str.size(); pos ++ )
    {
    unsigned char ch = str[pos];
    if ( (ch > 126 || ch < 32) && ch != 9  && ch != 10 && ch != 13 )
      {
      char buffer[33];
      sprintf(buffer, "&lt;%d&gt;", (int)ch);
      //sprintf(buffer, "&#x%0x;", (unsigned int)ch);
      ost << buffer;
      //lcnt += 4;
      }
    else
      {
      switch ( ch )
        {
        case '&': ost << "&amp;"; break;
        case '<': ost << "&lt;"; break;
        case '>': ost << "&gt;"; break;
        case '\n': ost << "\n"; 
          //lcnt = 0; 
          break;
        default: ost << ch;
        }
      //lcnt ++;
      }
    //if ( lcnt > 120 )
    //  {
    //  ost << "\n";
    //  lcnt = 0;
    //  }
    }
  return ost.str();
}

std::string cmCTest::MakeURLSafe(const std::string& str)
{
  cmOStringStream ost;
  char buffer[10];
  for ( std::string::size_type pos = 0; pos < str.size(); pos ++ )
    {
    unsigned char ch = str[pos];
    if ( ( ch > 126 || ch < 32 ||
           ch == '&' ||
           ch == '%' ||
           ch == '+' ||
           ch == '=' || 
           ch == '@'
          ) && ch != 9 )
      {
      sprintf(buffer, "%02x;", (unsigned int)ch);
      ost << buffer;
      }
    else
      {
      ost << ch;
      }
    }
  return ost.str();
}

bool TryExecutable(const char *dir, const char *file,
                   std::string *fullPath, const char *subdir)
{
  // try current directory
  std::string tryPath;
  if (dir && strcmp(dir,""))
    {
    tryPath = dir;
    tryPath += "/";
    }
  
  if (subdir && strcmp(subdir,""))
    {
    tryPath += subdir;
    tryPath += "/";
    }
  
  tryPath += file;
  if(cmSystemTools::FileExists(tryPath.c_str()))
    {
    *fullPath = cmSystemTools::CollapseFullPath(tryPath.c_str());
    return true;
    }
  tryPath += cmSystemTools::GetExecutableExtension();
  if(cmSystemTools::FileExists(tryPath.c_str()))
    {
    *fullPath = cmSystemTools::CollapseFullPath(tryPath.c_str());
    return true;
    }
  return false;
}

cmCTest::cmCTest() 
{ 
  m_ForceNewCTestProcess   = false;
  m_TomorrowTag            = false;
  m_BuildNoCMake           = false;
  m_BuildNoClean           = false;
  m_BuildTwoConfig         = false;
  m_UseIncludeRegExp       = false;
  m_UseExcludeRegExp       = false;
  m_UseExcludeRegExpFirst  = false;
  m_Verbose                = false;
  m_DartMode               = false;
  m_ShowOnly               = false;
  m_RunConfigurationScript = false;
  m_TestModel              = cmCTest::EXPERIMENTAL;
  m_InteractiveDebugMode   = true;
  m_TimeOut                = 0;
  m_CompatibilityMode      = 0;
  int cc; 
  for ( cc=0; cc < cmCTest::LAST_TEST; cc ++ )
    {
    m_Tests[cc] = 0;
    }
  m_ShortDateFormat        = true;
  m_MaximumPassedTestResultSize  = 100 * 1024;
  m_MaximumFailedTestResultSize  = 200 * 1024;

  this->ScriptHandler = new cmCTestScriptHandler;
  this->UpdateHandler = new cmCTestUpdateHandler;
  this->ConfigureHandler = new cmCTestConfigureHandler;
}

cmCTest::~cmCTest() 
{ 
  delete this->ScriptHandler;
  delete this->UpdateHandler;
  delete this->ConfigureHandler;
}

int cmCTest::Initialize()
{
  if(!m_InteractiveDebugMode)
    {
    this->BlockTestErrorDiagnostics();
    }
  
  m_ToplevelPath = cmSystemTools::GetCurrentWorkingDirectory();
  cmSystemTools::ConvertToUnixSlashes(m_ToplevelPath);
  if ( !this->ReadCustomConfigurationFileTree(m_ToplevelPath.c_str()) )
    {
    return 0;
    }
  this->UpdateCTestConfiguration();
  if ( m_DartMode )
    {
    std::string testingDir = m_ToplevelPath + "/Testing";
    if ( cmSystemTools::FileExists(testingDir.c_str()) )
      {
      if ( !cmSystemTools::FileIsDirectory(testingDir.c_str()) )
        {
        std::cerr << "File " << testingDir << " is in the place of the testing directory"
                  << std::endl;
        return 0;
        }
      }
    else
      {
      if ( !cmSystemTools::MakeDirectory(testingDir.c_str()) )
        {
        std::cerr << "Cannot create directory " << testingDir
                  << std::endl;
        return 0;
        }
      }
    std::string tagfile = testingDir + "/TAG";
    std::ifstream tfin(tagfile.c_str());
    std::string tag;
    time_t tctime = time(0);
    if ( m_TomorrowTag )
      {
      tctime += ( 24 * 60 * 60 );
      }
    struct tm *lctime = gmtime(&tctime);
    if ( tfin && cmSystemTools::GetLineFromStream(tfin, tag) )
      {
      int year = 0;
      int mon = 0;
      int day = 0;
      int hour = 0;
      int min = 0;
      sscanf(tag.c_str(), "%04d%02d%02d-%02d%02d",
             &year, &mon, &day, &hour, &min);
      if ( year != lctime->tm_year + 1900 ||
           mon != lctime->tm_mon+1 ||
           day != lctime->tm_mday )
        {
        tag = "";
        }
      std::string tagmode;
      if ( cmSystemTools::GetLineFromStream(tfin, tagmode) )
        {
        if ( tagmode.size() > 4 && !( m_Tests[cmCTest::START_TEST] || m_Tests[ALL_TEST] ))
          {
          m_TestModel = cmCTest::GetTestModelFromString(tagmode.c_str());
          }
        }
      tfin.close();
      }
    if ( tag.size() == 0 || m_Tests[cmCTest::START_TEST] || m_Tests[ALL_TEST])
      {
      //std::cout << "TestModel: " << this->GetTestModelString() << std::endl;
      //std::cout << "TestModel: " << m_TestModel << std::endl;
      if ( m_TestModel == cmCTest::NIGHTLY )
        {
        lctime = cmCTest::GetNightlyTime(m_DartConfiguration["NightlyStartTime"],
          m_Verbose,
          m_TomorrowTag);
        }
      char datestring[100];
      sprintf(datestring, "%04d%02d%02d-%02d%02d",
              lctime->tm_year + 1900,
              lctime->tm_mon+1,
              lctime->tm_mday,
              lctime->tm_hour,
              lctime->tm_min);
      tag = datestring;
      std::ofstream ofs(tagfile.c_str());
      if ( ofs )
        {
        ofs << tag << std::endl;
        ofs << this->GetTestModelString() << std::endl;
        }
      ofs.close();
      std::cout << "Create new tag: " << tag << " - " 
        << this->GetTestModelString() << std::endl;
      }
    m_CurrentTag = tag;
    }
  return 1;
}

void cmCTest::UpdateCTestConfiguration()
{
  // parse the dart test file
  std::ifstream fin("DartConfiguration.tcl");
  if(!fin)
    {
    return;
    }

  char buffer[1024];
  while ( fin )
    {
    buffer[0] = 0;
    fin.getline(buffer, 1023);
    buffer[1023] = 0;
    std::string line = ::CleanString(buffer);
    if(line.size() == 0)
      {
      continue;
      }
    while ( fin && (line[line.size()-1] == '\\') )
      {
      line = line.substr(0, line.size()-1);
      buffer[0] = 0;
      fin.getline(buffer, 1023);
      buffer[1023] = 0;
      line += ::CleanString(buffer);
      }
    if ( line[0] == '#' )
      {
      continue;
      }
    std::string::size_type cpos = line.find_first_of(":");
    if ( cpos == line.npos )
      {
      continue;
      }
    std::string key = line.substr(0, cpos);
    std::string value = ::CleanString(line.substr(cpos+1, line.npos));
    m_DartConfiguration[key] = value;
    }
  fin.close();
  if ( m_DartMode )
    {
    m_TimeOut = atoi(m_DartConfiguration["TimeOut"].c_str());
    }
}

void cmCTest::BlockTestErrorDiagnostics()
{
  cmSystemTools::PutEnv("DART_TEST_FROM_DART=1");
  cmSystemTools::PutEnv("DASHBOARD_TEST_FROM_CTEST=1");
#if defined(_WIN32)
  SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX); 
#endif
}

void cmCTest::SetTestModel(int mode)
{
  m_InteractiveDebugMode = false;
  m_TestModel = mode;
}

bool cmCTest::SetTest(const char* ttype, bool report)
{
  if ( cmSystemTools::LowerCase(ttype) == "all" )
    {
    m_Tests[cmCTest::ALL_TEST] = 1;
    }
  else if ( cmSystemTools::LowerCase(ttype) == "start" )
    {
    m_Tests[cmCTest::START_TEST] = 1;
    }
  else if ( cmSystemTools::LowerCase(ttype) == "update" )
    {
    m_Tests[cmCTest::UPDATE_TEST] = 1;
    }
  else if ( cmSystemTools::LowerCase(ttype) == "configure" )
    {
    m_Tests[cmCTest::CONFIGURE_TEST] = 1;
    }
  else if ( cmSystemTools::LowerCase(ttype) == "build" )
    {
    m_Tests[cmCTest::BUILD_TEST] = 1;
    }
  else if ( cmSystemTools::LowerCase(ttype) == "test" )
    {
    m_Tests[cmCTest::TEST_TEST] = 1;
    }
  else if ( cmSystemTools::LowerCase(ttype) == "coverage" )
    {
    m_Tests[cmCTest::COVERAGE_TEST] = 1;
    }
  else if ( cmSystemTools::LowerCase(ttype) == "memcheck" )
    {
    m_Tests[cmCTest::MEMCHECK_TEST] = 1;
    }
  else if ( cmSystemTools::LowerCase(ttype) == "notes" )
    {
    m_Tests[cmCTest::NOTES_TEST] = 1;
    }
  else if ( cmSystemTools::LowerCase(ttype) == "submit" )
    {
    m_Tests[cmCTest::SUBMIT_TEST] = 1;
    }
  else
    {
    if ( report )
      {
      std::cerr << "Don't know about test \"" << ttype << "\" yet..." << std::endl;
      }
    return false;
    }
  return true;
}

void cmCTest::Finalize()
{
}

std::string cmCTest::FindTheExecutable(const char *exe)
{
  std::string fullPath = "";
  std::string dir;
  std::string file;

  cmSystemTools::SplitProgramPath(exe, dir, file);
  if(m_ConfigType != "" && 
    ::TryExecutable(dir.c_str(), file.c_str(), &fullPath, 
      m_ConfigType.c_str()))
    {
    return fullPath;
    }

  if (::TryExecutable(dir.c_str(),file.c_str(),&fullPath,"."))
    {
    return fullPath;
    }

  if (::TryExecutable(dir.c_str(),file.c_str(),&fullPath,""))
    {
    return fullPath;
    }

  if ( m_ConfigType == "" )
    {
    // No config type, so try to guess it
    if (::TryExecutable(dir.c_str(),file.c_str(),&fullPath,"Release"))
      {
      return fullPath;
      }

    if (::TryExecutable(dir.c_str(),file.c_str(),&fullPath,"Debug"))
      {
      return fullPath;
      }

    if (::TryExecutable(dir.c_str(),file.c_str(),&fullPath,"MinSizeRel"))
      {
      return fullPath;
      }

    if (::TryExecutable(dir.c_str(),file.c_str(),&fullPath,"RelWithDebInfo"))
      {
      return fullPath;
      }
    }

  // if everything else failed, check the users path
  if (dir != "")
    {
    std::string path = cmSystemTools::FindProgram(file.c_str());
    if (path != "")
      {
      return path;
      }
    }

  if ( m_ConfigType != "" )
    {
    dir += "/";
    dir += m_ConfigType;
    dir += "/";
    dir += file;
    cmSystemTools::Error("config type specified on the command line, but test executable not found.",
      dir.c_str());
    return "";
    }
  return fullPath;
}


int cmCTest::BuildDirectory()
{
  std::cout << "Build project" << std::endl;
  std::string makeCommand = m_DartConfiguration["MakeCommand"];
  if ( makeCommand.size() == 0 )
    {
    std::cerr << "Cannot find MakeCommand key in the DartConfiguration.tcl" << std::endl;
    return 1;
    }
  std::string buildDirectory = m_DartConfiguration["BuildDirectory"];
  if ( buildDirectory.size() == 0 )
    {
    std::cerr << "Cannot find BuildDirectory  key in the DartConfiguration.tcl" << std::endl;
    return 1;
    }

  std::ofstream ofs;
  double elapsed_time_start = cmSystemTools::GetTime();
  if ( !this->OpenOutputFile("Temporary", "LastBuild.log", ofs) )
    {
    std::cerr << "Cannot create LastBuild.log file" << std::endl;    
    }
  m_StartBuild = this->CurrentTime();
  std::string output;
  int retVal = 0;
  int res = cmsysProcess_State_Exited;
  if ( !m_ShowOnly )
    {
    res = this->RunMakeCommand(makeCommand.c_str(), &output, 
      &retVal, buildDirectory.c_str(), 
      m_Verbose, 0, ofs);
    }
  else
    {
    std::cout << "Build with command: " << makeCommand << std::endl;
    }
  m_EndBuild = this->CurrentTime();
  double elapsed_build_time = cmSystemTools::GetTime() - elapsed_time_start;
  if (res != cmsysProcess_State_Exited || retVal )
    {
    std::cerr << "Error(s) when building project" << std::endl;
    }
  if ( ofs )
    {
    ofs.close();
    }

  tm_VectorOfStrings::size_type cc;
  if ( m_DartConfiguration["SourceDirectory"].size() > 20 ||
    m_DartConfiguration["BuildDirectory"].size() > 20 )
    {
    std::string srcdir = m_DartConfiguration["SourceDirectory"] + "/";
    std::string bindir = m_DartConfiguration["BuildDirectory"] + "/";
    std::string srcdirrep;
    std::string bindirrep;
    for ( cc = srcdir.size()-2; cc > 0; cc -- )
      {
      if ( srcdir[cc] == '/' )
        {
        srcdirrep = srcdir.c_str() + cc;
        srcdirrep = "/..." + srcdirrep;
        srcdir = srcdir.substr(0, cc+1);
        break;
        }
      }
    for ( cc = bindir.size()-2; cc > 0; cc -- )
      {
      if ( bindir[cc] == '/' )
        {
        bindirrep = bindir.c_str() + cc;
        bindirrep = "/..." + bindirrep;
        bindir = bindir.substr(0, cc+1);
        break;
        }
      }

    cmSystemTools::ReplaceString(output, srcdir.c_str(), "/.../"); //srcdirrep.c_str());
    cmSystemTools::ReplaceString(output, bindir.c_str(), "/.../"); //bindirrep.c_str());
    }

  // Parsing of output for errors and warnings.

  std::vector<cmStdString> lines;
  cmSystemTools::Split(output.c_str(), lines);

  
  // Lines are marked: 
  // 0 - nothing
  // 1 - error
  // > 1 - warning
  std::vector<int> markedLines(lines.size(), 0);
  
  // Errors
  for ( cc = 0; cmCTestErrorMatches[cc]; cc ++ )
    {
    m_CustomErrorMatches.push_back(cmCTestErrorMatches[cc]);
    }
  for ( cc = 0; cmCTestErrorExceptions[cc]; cc ++ )
    {
    m_CustomErrorExceptions.push_back(cmCTestErrorExceptions[cc]);
    }
  for ( cc = 0; cmCTestWarningMatches[cc]; cc ++ )
    {
    m_CustomWarningMatches.push_back(cmCTestWarningMatches[cc]);
    }
  for ( cc = 0; cmCTestWarningExceptions[cc]; cc ++ )
    {
    m_CustomWarningExceptions.push_back(cmCTestWarningExceptions[cc]);
    }

  for ( cc = 0; cc < m_CustomErrorMatches.size(); cc ++ )
    {
    cmsys::RegularExpression re(m_CustomErrorMatches[cc].c_str());
    cmCTest::tm_VectorOfStrings::size_type kk;
    for ( kk = 0; kk < lines.size(); kk ++ )
      {
      if ( re.find(lines[kk]) )
        {
        markedLines[kk] = 1;
        }
      }    
    }
  // Warnings
  for ( cc = 0; cc < m_CustomWarningMatches.size(); cc ++ )
    {
    cmsys::RegularExpression re(m_CustomWarningMatches[cc].c_str());
    cmCTest::tm_VectorOfStrings::size_type kk;
    for ( kk = 0; kk < lines.size(); kk ++ )
      {
      if ( re.find(lines[kk]) )
        {
        markedLines[kk] += 2;
        }
      }    
    }
  // Errors exceptions
  for ( cc = 0; cc < m_CustomErrorExceptions.size(); cc ++ )
    {
    cmsys::RegularExpression re(m_CustomErrorExceptions[cc].c_str());
    std::vector<int>::size_type kk;
    for ( kk =0; kk < markedLines.size(); kk ++ )
      {
      if ( markedLines[kk] == 1 )
        {
        if ( re.find(lines[kk]) )
          {
          markedLines[kk] = 0;
          }
        }
      }
    }
  // Warning exceptions
  for ( cc = 0; cc < m_CustomWarningExceptions.size(); cc ++ )
    {
    cmsys::RegularExpression re(m_CustomWarningExceptions[cc].c_str());
    std::vector<int>::size_type kk;
    for ( kk =0; kk < markedLines.size(); kk ++ )
      {
      if ( markedLines[kk] > 1 )
        {
        if ( re.find(lines[kk]) )
          {
          markedLines[kk] = 0;
          }
        }
      }
    }
  std::vector<cmCTestBuildErrorWarning> errorsWarnings;

  int errors = 0;
  int warnings = 0;

  std::vector<int>::size_type kk;
  cmCTestBuildErrorWarning errorwarning;
  for ( kk =0; kk < markedLines.size(); kk ++ )
    {
    errorwarning.m_LineNumber = -1;
    bool found = false;
    if ( markedLines[kk] == 1 )
      {
      //std::cout << "Error: " << lines[kk] << std::endl;
      errorwarning.m_Error = true;
      found = true;
      }
    else if ( markedLines[kk] > 1 )
      {
      //std::cout << "Warning: " << lines[kk] << std::endl;
      errorwarning.m_Error = false;
      found = true;
      }
    if ( found )
      {
      errorwarning.m_LogLine     = static_cast<int>(kk+1);
      errorwarning.m_Text        = lines[kk];
      errorwarning.m_PreContext  = "";
      errorwarning.m_PostContext = "";
      std::vector<int>::size_type jj;
      std::vector<int>::size_type ll = 0;
      if ( kk > 6 )
        {
        ll = kk - 6;
        }
      for ( jj = kk-1; 
            jj > 0 && jj > ll && markedLines[jj] != markedLines[kk]; 
            jj -- );
      while ( markedLines[jj] == markedLines[kk] && jj < kk )
        {
        jj ++;
        }
      for (; jj < kk; jj ++ )
        {
        errorwarning.m_PreContext += lines[jj] + "\n";
        }
      for ( jj = kk+1; 
            jj < lines.size() && jj < kk + 7 && markedLines[jj] != markedLines[kk]; 
            jj ++ )
        {
        errorwarning.m_PostContext += lines[jj] + "\n";
        }
      errorsWarnings.push_back(errorwarning);
      if ( errorwarning.m_Error )
        {
        errors ++;
        }
      else
        {
        warnings ++;
        }
      }
    }

  std::cout << "   " << errors << " Compiler errors" << std::endl;
  std::cout << "   " << warnings << " Compiler warnings" << std::endl;

  if( !this->OpenOutputFile(m_CurrentTag, "Build.xml", ofs) )
    {
    std::cerr << "Cannot create build XML file" << std::endl;
    return 1;
    }
  this->GenerateDartBuildOutput(ofs, errorsWarnings, elapsed_build_time);
  return 0;
}
 
int cmCTest::CoverageDirectory()
{
  std::cout << "Performing coverage" << std::endl;
  double elapsed_time_start = cmSystemTools::GetTime();
  cmCTest::tm_VectorOfStrings files;
  cmCTest::tm_VectorOfStrings cfiles;
  cmCTest::tm_VectorOfStrings cdirs;
  bool done = false;
  std::string::size_type cc;
  std::string glob;
  std::map<std::string, std::string> allsourcefiles;
  std::map<std::string, std::string> allbinaryfiles;

  std::string start_time = this->CurrentTime();

  // Find all source files.
  std::string sourceDirectory = m_DartConfiguration["SourceDirectory"];
  if ( sourceDirectory.size() == 0 )
    {
    std::cerr << "Cannot find SourceDirectory key in the DartConfiguration.tcl" << std::endl;
    return 1;
    }

  std::string coverageCommand = m_DartConfiguration["CoverageCommand"];
  if ( coverageCommand.size() == 0 )
    {
    std::cerr << "Coverage command not defined in DartConfiguration.tcl" << std::endl;
    return 1;
    }
  cdirs.push_back(sourceDirectory);
  while ( !done ) 
    {
    if ( cdirs.size() <= 0 )
      {
      break;
      }
    glob = cdirs[cdirs.size()-1] + "/*";
    //std::cout << "Glob: " << glob << std::endl;
    cdirs.pop_back();
    if ( cmSystemTools::SimpleGlob(glob, cfiles, 1) )
      {
      for ( cc = 0; cc < cfiles.size(); cc ++ )
        {
        allsourcefiles[cmSystemTools::GetFilenameName(cfiles[cc])] = cfiles[cc];
        }
      }
    if ( cmSystemTools::SimpleGlob(glob, cfiles, -1) )
      {
      for ( cc = 0; cc < cfiles.size(); cc ++ )
        {
        if ( cfiles[cc] != "." && cfiles[cc] != ".." )
          {
          cdirs.push_back(cfiles[cc]);
          }
        }
      }
    }

  // find all binary files
  cdirs.push_back(cmSystemTools::GetCurrentWorkingDirectory());
  while ( !done ) 
    {
    if ( cdirs.size() <= 0 )
      {
      break;
      }
    glob = cdirs[cdirs.size()-1] + "/*";
    //std::cout << "Glob: " << glob << std::endl;
    cdirs.pop_back();
    if ( cmSystemTools::SimpleGlob(glob, cfiles, 1) )
      {
      for ( cc = 0; cc < cfiles.size(); cc ++ )
        {
        allbinaryfiles[cmSystemTools::GetFilenameName(cfiles[cc])] = cfiles[cc];
        }
      }
    if ( cmSystemTools::SimpleGlob(glob, cfiles, -1) )
      {
      for ( cc = 0; cc < cfiles.size(); cc ++ )
        {
        if ( cfiles[cc] != "." && cfiles[cc] != ".." )
          {
          cdirs.push_back(cfiles[cc]);
          }
        }
      }
    }

  std::map<std::string, std::string>::iterator sit;
  for ( sit = allbinaryfiles.begin(); sit != allbinaryfiles.end(); sit ++ )
    {
    const std::string& fname = sit->second;
    //std::cout << "File: " << fname << std::endl;
    if ( strcmp(fname.substr(fname.size()-3, 3).c_str(), ".da") == 0 )
      {
      files.push_back(fname);
      }
    }
  
  if ( files.size() == 0 )
    {
    std::cerr << "Cannot find any coverage information files (.da)" << std::endl;
    return 1;
    }

  std::ofstream log; 
  if (!this->OpenOutputFile("Temporary", "Coverage.log", log))
    {
    std::cerr << "Cannot open log file" << std::endl;
    return 1;
    }
  log.close();
  if (!this->OpenOutputFile(m_CurrentTag, "Coverage.xml", log))
    {
    std::cerr << "Cannot open log file" << std::endl;
    return 1;
    }

  std::string opath = m_ToplevelPath + "/Testing/Temporary/Coverage";
  cmSystemTools::MakeDirectory(opath.c_str());
  cfiles.clear();
  cmCTest::tm_VectorOfStrings ncfiles;
  cmCTest::tm_VectorOfStrings missing_files;

  for ( cc = 0; cc < files.size(); cc ++ )
    {
    std::string currPath = cmSystemTools::GetFilenamePath(files[cc]);
    std::string command = coverageCommand + " -o \"" + currPath + "\" -l \"" + files[cc] + "\"";
    std::string output;
    int retVal = 0;
    if ( m_Verbose )
      {
      std::cerr << "Run gcov on " << files[cc] << " in directory: " << currPath.c_str() << std::endl;
      }
    //std::cout << "   --- Run [" << command << "]" << std::endl;
    bool res = true;
    if ( !m_ShowOnly )
      {
      res = cmSystemTools::RunSingleCommand(command.c_str(), &output, 
        &retVal, currPath.c_str(),
        m_Verbose, 0 /*m_TimeOut*/);
      }
    if ( res && retVal == 0 )
      {
      //std::cout << " - done" << std::endl;
      glob = currPath + "/*";
      if ( !cmSystemTools::SimpleGlob(glob, ncfiles, 1) )
        {
        std::cerr << "Cannot found any coverage files" << std::endl;
        return 1;
        }
      cfiles.insert(cfiles.end(), ncfiles.begin(), ncfiles.end());
      std::vector<cmStdString> gcovlines;
      cmSystemTools::Split(output.c_str(), gcovlines);
      std::vector<cmStdString>::iterator git;
      const char* message = "Could not open source file";
      for ( git = gcovlines.begin(); git != gcovlines.end(); ++git )
        {
        if ( strncmp(git->c_str(), message, strlen(message) ) == 0 )
          {
          std::cerr << "Problem: " << git->c_str() << std::endl;
          missing_files.push_back(git->c_str() + strlen(message));
          }
        }
      }
    else
      {
      std::cerr << "Run gcov on " << files[cc] << std::flush;
      std::cerr << " [" << command << "]" << std::endl;
      std::cerr << " - fail" << std::endl;
      }
    }
  
  files.clear();
  std::map<std::string, cmCTest::tm_VectorOfStrings > sourcefiles;
  for ( cc = 0; cc < cfiles.size(); cc ++ )
    {
    std::string& fname = cfiles[cc];
    //    std::cout << "File: " << fname << std::endl;
    if ( strcmp(fname.substr(fname.size()-5, 5).c_str(), ".gcov") == 0 )
      {
      files.push_back(fname);
      std::string::size_type pos = fname.find(".da.");
      std::string::size_type pos2 = fname.find(".da##");
      if(pos2 != fname.npos)
        {
        pos = pos2+1;
        }
      if ( pos != fname.npos )
        {
        pos += 4;
        std::string::size_type epos = fname.size() - pos - strlen(".gcov");
        std::string nf = fname.substr(pos, epos);
        //std::cout << "Substring: " << nf << std::endl;
        if ( allsourcefiles.find(nf) != allsourcefiles.end() || 
             allbinaryfiles.find(nf) != allbinaryfiles.end() )
          {
          cmCTest::tm_VectorOfStrings &cvec = sourcefiles[nf];
          cvec.push_back(fname);
          }
        }
      }
    }
  // for ( cc = 0; cc < files.size(); cc ++ )
  //     {
  //     std::cout << "File: " << files[cc] << std::endl;
  //     }
  if ( missing_files.size() > 0 )
    {
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << "The following files were missing:" << std::endl;
    for ( cc = 0; cc < missing_files.size(); cc ++ )
      {
      std::cout << "File: " << missing_files[cc] << std::endl;
      }
    std::cout << "---------------------------------------------------------------" << std::endl;
    }

  std::map<std::string, cmCTest::tm_VectorOfStrings >::iterator it;
  cmCTest::tm_CoverageMap coverageresults;

  this->StartXML(log);
  log << "<Coverage>\n"
      << "\t<StartDateTime>" << start_time << "</StartDateTime>" << std::endl;

  int total_tested = 0;
  int total_untested = 0;

  for ( it = sourcefiles.begin(); it != sourcefiles.end(); it ++ )
    {
    //std::cerr << "Source file: " << it->first << std::endl;
    cmCTest::tm_VectorOfStrings &gfiles = it->second;

    for ( cc = 0; cc < gfiles.size(); cc ++ )
      {
      int do_coverage = 1;
      std::string coverage_dir = cmSystemTools::GetFilenamePath(gfiles[cc].c_str());
      std::string builDir = m_DartConfiguration["BuildDirectory"];
      do
        {
        std::string coverage_file = coverage_dir + "/.NoDartCoverage";
        if ( cmSystemTools::FileExists(coverage_file.c_str()) )
          {
          do_coverage = 0;
          break;
          }
        // is there a parent directory we can check
        std::string::size_type pos = coverage_dir.rfind('/');
        // if we could not find the directory return 0
        if(pos == std::string::npos)
          {
          break;
          }
        coverage_dir = coverage_dir.substr(0, pos);
        }
      while (coverage_dir.size() >= builDir.size());
      if ( !do_coverage )
        {
        continue;
        }
      //std::cout << "\t" << gfiles[cc] << std::endl;
      std::ifstream ifile(gfiles[cc].c_str());
      if ( !ifile )
        {
        std::cerr << "Cannot open file: " << gfiles[cc].c_str() << std::endl;
        }

      ifile.seekg (0, std::ios::end);
      int length = ifile.tellg();
      ifile.seekg (0, std::ios::beg);
      char *buffer = new char [ length + 1 ];
      ifile.read(buffer, length);
      buffer [length] = 0;
      //std::cout << "Read: " << buffer << std::endl;
      std::vector<cmStdString> lines;
      cmSystemTools::Split(buffer, lines);
      delete [] buffer;
      cmCTest::cmCTestCoverage& cov = coverageresults[it->first];
      std::vector<int>& covlines = cov.m_Lines; 
      if ( cov.m_FullPath == "" )
        {
        covlines.insert(covlines.begin(), lines.size(), -1);
        if ( allsourcefiles.find(it->first) != allsourcefiles.end() )
          {
          cov.m_FullPath = allsourcefiles[it->first];
          }
        else if ( allbinaryfiles.find(it->first) != allbinaryfiles.end() )
          {
          cov.m_FullPath = allbinaryfiles[it->first];
          }
        cov.m_AbsolutePath = cov.m_FullPath;
        std::string src_dir = m_DartConfiguration["SourceDirectory"];
        if ( src_dir[src_dir.size()-1] != '/' )
          {
          src_dir = src_dir + "/";
          }
        std::string::size_type spos = cov.m_FullPath.find(src_dir);
        if ( spos == 0 )
          {
          cov.m_FullPath = std::string("./") + cov.m_FullPath.substr(src_dir.size());
          }
        else
          {
          //std::cerr << "Compare -- " << cov.m_FullPath << std::endl;
          //std::cerr << "        -- " << src_dir << std::endl;
          cov.m_Show = false;
          continue;
          }
        cov.m_Show = true;
        }
      std::string::size_type kk;
      //      std::cerr << "number of lines " << lines.size() << "\n";
      for ( kk = 0; kk < lines.size(); kk ++ )
        {
        std::string& line = lines[kk];
        //std::cerr << line << "\n";
        std::string sub1 = line.substr(0, strlen("    #####"));
        std::string sub2 = line.substr(0, strlen("      ######"));
        int count = atoi(sub2.c_str());
        if ( sub1.compare("    #####") == 0 ||
             sub2.compare("      ######") == 0 )
          {
          if ( covlines[kk] == -1 )
            {
            covlines[kk] = 0;
            }
          cov.m_UnTested ++;
          //std::cout << "Untested - ";
          }
        else if ( count > 0 )
          {
          if ( covlines[kk] == -1 )
            {
            covlines[kk] = 0;
            }
          cov.m_Tested ++;
          covlines[kk] ++;
          //std::cout << "Tested[" << count << "] - ";
          }

        //std::cout << line << std::endl;
        }
      }
    }

  //std::cerr << "Finalizing" << std::endl;
  cmCTest::tm_CoverageMap::iterator cit;
  int ccount = 0;
  std::ofstream cfileoutput; 
  int cfileoutputcount = 0;
  char cfileoutputname[100];
  std::string local_start_time = this->CurrentTime();
  std::string local_end_time;
  for ( cit = coverageresults.begin(); cit != coverageresults.end(); cit ++ )
    {
    cmCTest::cmCTestCoverage &cov = cit->second;
    if ( !cov.m_Show )
      {
      continue;
      }

    // Check if we should ignore the directory, if we find a NoDartCoverage
    // file in it or any of its parents
    int do_coverage = 1;
    std::string coverage_dir = cmSystemTools::GetFilenamePath(cov.m_AbsolutePath.c_str());
    do
      {
      std::string coverage_file = coverage_dir + "/.NoDartCoverage";
      if ( cmSystemTools::FileExists(coverage_file.c_str()) )
        {
        do_coverage = 0;
        break;
        }
      // is there a parent directory we can check
      std::string::size_type pos = coverage_dir.rfind('/');
      // if we could not find the directory return 0
      if(pos == std::string::npos)
        {
        break;
        }
      coverage_dir = coverage_dir.substr(0, pos);

      }
    while (coverage_dir.size() >= sourceDirectory.size());

    if (!do_coverage)
      {
      if ( m_Verbose )
        {
        std::cout << "Ignore file: " << cov.m_FullPath.c_str() << std::endl;
        }
      continue;
      }
    
    if ( ccount == 100 )
      {
      local_end_time = this->CurrentTime();
      cfileoutput << "\t<EndDateTime>" << local_end_time << "</EndDateTime>\n"
        << "</CoverageLog>" << std::endl;
      this->EndXML(cfileoutput);
      cfileoutput.close();
      std::cout << "Close file: " << cfileoutputname << std::endl;
      ccount = 0;
      }
    if ( ccount == 0 )
      {
      sprintf(cfileoutputname, "CoverageLog-%d.xml", cfileoutputcount++);
      std::cout << "Open file: " << cfileoutputname << std::endl;
      if (!this->OpenOutputFile(m_CurrentTag, cfileoutputname, cfileoutput))
        {
        std::cerr << "Cannot open log file: " << cfileoutputname << std::endl;
        return 1;
        }
      local_start_time = this->CurrentTime();
      this->StartXML(cfileoutput);
      cfileoutput << "<CoverageLog>\n"
        << "\t<StartDateTime>" << local_start_time << "</StartDateTime>" << std::endl;
      }

    //std::cerr << "Final process of Source file: " << cit->first << std::endl;
    cov.m_UnTested = 0;
    cov.m_Tested = 0;
    for ( cc = 0; cc < cov.m_Lines.size(); cc ++ )
      {
      if ( cov.m_Lines[cc] == 0 )
        {
        cov.m_UnTested ++;
        }
      else if ( cov.m_Lines[cc] > 0 )
        {
        cov.m_Tested ++;
        }
      }

    std::ifstream ifile(cov.m_AbsolutePath.c_str());
    if ( !ifile )
      {
      std::cerr << "Cannot open file: " << cov.m_FullPath.c_str() << std::endl;
      }
    ifile.seekg (0, std::ios::end);
    int length = ifile.tellg();
    ifile.seekg (0, std::ios::beg);
    char *buffer = new char [ length + 1 ];
    ifile.read(buffer, length);
    buffer [length] = 0;
    //std::cout << "Read: " << buffer << std::endl;
    std::vector<cmStdString> lines;
    cmSystemTools::Split(buffer, lines);
    delete [] buffer;

    cfileoutput << "\t<File Name=\"" << cit->first << "\" FullPath=\""
      << cov.m_FullPath << "\">\n"
      << "\t\t<Report>" << std::endl;
    for ( cc = 0; cc < lines.size(); cc ++ )
      {
      cfileoutput << "\t\t<Line Number=\"" 
        << static_cast<int>(cc) << "\" Count=\""
        << cov.m_Lines[cc] << "\">"
        << cmCTest::MakeXMLSafe(lines[cc]) << "</Line>" << std::endl;
      }
    cfileoutput << "\t\t</Report>\n"
      << "\t</File>" << std::endl;


    total_tested += cov.m_Tested;
    total_untested += cov.m_UnTested;
    float cper = 0;
    float cmet = 0;
    if ( total_tested + total_untested > 0 && (cov.m_Tested + cov.m_UnTested) > 0)
      {
      cper = (100 * SAFEDIV(static_cast<float>(cov.m_Tested),
        static_cast<float>(cov.m_Tested + cov.m_UnTested)));
      cmet = ( SAFEDIV(static_cast<float>(cov.m_Tested + 10),
        static_cast<float>(cov.m_Tested + cov.m_UnTested + 10)));
      }

    log << "\t<File Name=\"" << cit->first << "\" FullPath=\"" << cov.m_FullPath
      << "\" Covered=\"" << (cmet>0?"true":"false") << "\">\n"
      << "\t\t<LOCTested>" << cov.m_Tested << "</LOCTested>\n"
      << "\t\t<LOCUnTested>" << cov.m_UnTested << "</LOCUnTested>\n"
      << "\t\t<PercentCoverage>";
    log.setf(std::ios::fixed, std::ios::floatfield);
    log.precision(2);
    log << (cper) << "</PercentCoverage>\n"
      << "\t\t<CoverageMetric>";
    log.setf(std::ios::fixed, std::ios::floatfield);
    log.precision(2);
    log << (cmet) << "</CoverageMetric>\n"
      << "\t</File>" << std::endl;
    ccount ++;
    }
  
  if ( ccount > 0 )
    {
    local_end_time = this->CurrentTime();
    cfileoutput << "\t<EndDateTime>" << local_end_time << "</EndDateTime>\n"
                << "</CoverageLog>" << std::endl;
    this->EndXML(cfileoutput);
    cfileoutput.close();
    }

  int total_lines = total_tested + total_untested;
  float percent_coverage = 100 * SAFEDIV(static_cast<float>(total_tested),
    static_cast<float>(total_lines));
  if ( total_lines == 0 )
    {
    percent_coverage = 0;
    }

  std::string end_time = this->CurrentTime();

  log << "\t<LOCTested>" << total_tested << "</LOCTested>\n"
      << "\t<LOCUntested>" << total_untested << "</LOCUntested>\n"
      << "\t<LOC>" << total_lines << "</LOC>\n"
      << "\t<PercentCoverage>";
  log.setf(std::ios::fixed, std::ios::floatfield);
  log.precision(2);
  log << (percent_coverage)<< "</PercentCoverage>\n"
      << "\t<EndDateTime>" << end_time << "</EndDateTime>\n";
  log << "<ElapsedMinutes>" << 
    static_cast<int>((cmSystemTools::GetTime() - elapsed_time_start)/6)/10.0
      << "</ElapsedMinutes>"
      << "</Coverage>" << std::endl;
  this->EndXML(log);

  std::cout << "\tCovered LOC:         " << total_tested << std::endl
            << "\tNot covered LOC:     " << total_untested << std::endl
            << "\tTotal LOC:           " << total_lines << std::endl
            << "\tPercentage Coverage: ";

  std::cout.setf(std::ios::fixed, std::ios::floatfield);
  std::cout.precision(2);
  std::cout << (percent_coverage) << "%" << std::endl;


  return 1;
}

bool cmCTest::OpenOutputFile(const std::string& path, 
                     const std::string& name, std::ofstream& stream)
{
  std::string testingDir = m_ToplevelPath + "/Testing";
  if ( path.size() > 0 )
    {
    testingDir += "/" + path;
    }
  if ( cmSystemTools::FileExists(testingDir.c_str()) )
    {
    if ( !cmSystemTools::FileIsDirectory(testingDir.c_str()) )
      {
      std::cerr << "File " << testingDir 
                << " is in the place of the testing directory"
                << std::endl;
      return false;
      }
    }
  else
    {
    if ( !cmSystemTools::MakeDirectory(testingDir.c_str()) )
      {
      std::cerr << "Cannot create directory " << testingDir
                << std::endl;
      return false;
      }
    }
  std::string filename = testingDir + "/" + name;
  stream.open(filename.c_str());
  if( !stream )
    {
    std::cerr << "Problem opening file: " << filename << std::endl;
    return false;
    }
  return true;
}

void cmCTest::GenerateDartBuildOutput(std::ostream& os, 
                                      std::vector<cmCTestBuildErrorWarning> ew,
                                      double elapsed_build_time)
{
  this->StartXML(os);
  os << "<Build>\n"
     << "\t<StartDateTime>" << m_StartBuild << "</StartDateTime>\n"
     << "<BuildCommand>" 
     << this->MakeXMLSafe(m_DartConfiguration["MakeCommand"])
     << "</BuildCommand>" << std::endl;
    
  std::vector<cmCTestBuildErrorWarning>::iterator it;
  for ( it = ew.begin(); it != ew.end(); it++ )
    {
    cmCTestBuildErrorWarning *cm = &(*it);
    os << "\t<" << (cm->m_Error ? "Error" : "Warning") << ">\n"
       << "\t\t<BuildLogLine>" << cm->m_LogLine << "</BuildLogLine>\n"
       << "\t\t<Text>" << this->MakeXMLSafe(cm->m_Text) 
       << "\n</Text>" << std::endl;
    if ( cm->m_SourceFile.size() > 0 )
      {
      os << "\t\t<SourceFile>" << cm->m_SourceFile << "</SourceFile>" 
         << std::endl;
      }
    if ( cm->m_SourceFileTail.size() > 0 )
      {
      os << "\t\t<SourceFileTail>" << cm->m_SourceFileTail 
         << "</SourceFileTail>" << std::endl;
      }
    if ( cm->m_LineNumber >= 0 )
      {
      os << "\t\t<SourceLineNumber>" << cm->m_LineNumber 
         << "</SourceLineNumber>" << std::endl;
      }
    os << "\t\t<PreContext>" << this->MakeXMLSafe(cm->m_PreContext) 
       << "</PreContext>\n"
       << "\t\t<PostContext>" << this->MakeXMLSafe(cm->m_PostContext) 
       << "</PostContext>\n"
       << "\t\t<RepeatCount>0</RepeatCount>\n"
       << "</" << (cm->m_Error ? "Error" : "Warning") << ">\n\n" 
       << std::endl;
    }
  os << "\t<Log Encoding=\"base64\" Compression=\"/bin/gzip\">\n\t</Log>\n"
     << "\t<EndDateTime>" << m_EndBuild << "</EndDateTime>\n"
     << "<ElapsedMinutes>" << static_cast<int>(elapsed_build_time/6)/10.0
     << "</ElapsedMinutes>"
     << "</Build>" << std::endl;
  this->EndXML(os);
}
  
void cmCTest::GetListOfTests(tm_ListOfTests* testlist, bool memcheck)
{
  // does the DartTestfile.txt exist ?
  if(!cmSystemTools::FileExists("DartTestfile.txt"))
    {
    return;
    }

  // parse the file
  std::ifstream fin("DartTestfile.txt");
  if(!fin)
    {
    return;
    }

  cmsys::RegularExpression ireg(this->m_IncludeRegExp.c_str());
  cmsys::RegularExpression ereg(this->m_ExcludeRegExp.c_str());

  cmListFileCache cache;
  cmListFile* listFile = cache.GetFileCache("DartTestfile.txt", false);
  for(std::vector<cmListFileFunction>::const_iterator f =
    listFile->m_Functions.begin(); f != listFile->m_Functions.end(); ++f)
    {
    const cmListFileFunction& lff = *f;
    const std::string& name = lff.m_Name;
    const tm_VectorOfListFileArgs& args = lff.m_Arguments;
    if (name == "SUBDIRS")
      {
      std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
      for(tm_VectorOfListFileArgs::const_iterator j = args.begin();
        j != args.end(); ++j)
        {
        std::string nwd = cwd + "/";
        nwd += j->Value;
        if (cmSystemTools::FileIsDirectory(nwd.c_str()))
          {
          cmSystemTools::ChangeDirectory(nwd.c_str());
          this->GetListOfTests(testlist, memcheck);
          }
        }
      // return to the original directory
      cmSystemTools::ChangeDirectory(cwd.c_str());
      }

    if (name == "ADD_TEST")
      {
      const std::string& testname = args[0].Value;
      if (this->m_UseExcludeRegExp &&
        this->m_UseExcludeRegExpFirst &&
        ereg.find(testname.c_str()))
        {
        continue;
        }
      if ( memcheck )
        {
        tm_VectorOfStrings::iterator it;
        bool found = false;
        for ( it = m_CustomMemCheckIgnore.begin(); 
          it != m_CustomMemCheckIgnore.end(); ++ it )
          {
          if ( *it == testname )
            {
            found = true;
            break;
            }
          }
        if ( found )
          {
          if ( m_Verbose )
            {
            std::cout << "Ignore memcheck: " << *it << std::endl;
            }
          continue;
          }
        }
      else
        {
        tm_VectorOfStrings::iterator it;
        bool found = false;
        for ( it = m_CustomTestsIgnore.begin(); 
          it != m_CustomTestsIgnore.end(); ++ it )
          {
          if ( *it == testname )
            {
            found = true;
            break;
            }
          }
        if ( found )
          {
          if ( m_Verbose )
            {
            std::cout << "Ignore test: " << *it << std::endl;
            }
          continue;
          }
        }


      if (this->m_UseIncludeRegExp && !ireg.find(testname.c_str()))
        {
        continue;
        }
      if (this->m_UseExcludeRegExp &&
        !this->m_UseExcludeRegExpFirst &&
        ereg.find(testname.c_str()))
        {
        continue;
        }

      cmCTestTestProperties test;
      test.m_Name = testname;
      test.m_Args = args;
      test.m_Directory = cmSystemTools::GetCurrentWorkingDirectory();
      testlist->push_back(test);
      }
    }
}

void cmCTest::ProcessDirectory(cmCTest::tm_VectorOfStrings &passed, 
                             cmCTest::tm_VectorOfStrings &failed,
                             bool memcheck)
{
  std::string current_dir = cmSystemTools::GetCurrentWorkingDirectory();
  cmsys::RegularExpression dartStuff("(<DartMeasurement.*/DartMeasurement[a-zA-Z]*>)");
  tm_ListOfTests testlist;
  this->GetListOfTests(&testlist, memcheck);
  tm_ListOfTests::size_type tmsize = testlist.size();

  std::ofstream ofs;
  std::ofstream *olog = 0;
  if ( !m_ShowOnly && tmsize > 0 && 
    this->OpenOutputFile("Temporary", 
      (memcheck?"LastMemCheck.log":"LastTest.log"), ofs) )
    {
    olog = &ofs;
    }

  m_StartTest = this->CurrentTime();
  double elapsed_time_start = cmSystemTools::GetTime();

  if ( olog )
    {
    *olog << "Start testing: " << m_StartTest << std::endl
      << "----------------------------------------------------------"
      << std::endl;
    }

  // expand the test list
  this->ExpandTestsToRunInformation((int)tmsize);
  
  int cnt = 0;
  tm_ListOfTests::iterator it;
  std::string last_directory = "";
  for ( it = testlist.begin(); it != testlist.end(); it ++ )
    {
    cnt ++;
    const std::string& testname = it->m_Name;
    tm_VectorOfListFileArgs& args = it->m_Args;
    cmCTestTestResult cres;
    cres.m_Status = cmCTest::NOT_RUN;
    cres.m_TestCount = cnt;

    if (!(last_directory == it->m_Directory))
      {
      if ( m_Verbose )
        {
        std::cerr << "Changing directory into " 
          << it->m_Directory.c_str() << "\n";
        }
      last_directory = it->m_Directory;
      cmSystemTools::ChangeDirectory(it->m_Directory.c_str());
      }
    cres.m_Name = testname;
    if(m_TestsToRun.size() && 
       std::find(m_TestsToRun.begin(), m_TestsToRun.end(), cnt) == m_TestsToRun.end())
      {
      continue;
      }

    if ( m_ShowOnly )
      {
      std::cerr.width(3);
      std::cerr << cnt << "/";
      std::cerr.width(3);
      std::cerr << tmsize << " Testing ";
      std::string outname = testname;
      outname.resize(30, ' ');
      std::cerr << outname.c_str() << "\n";
     }
    else
      {
      std::cerr.width(3);
      std::cerr << cnt << "/";
      std::cerr.width(3);
      std::cerr << tmsize << " Testing ";
      std::string outname = testname;
      outname.resize(30, ' ');
      std::cerr << outname.c_str();
      std::cerr.flush();
      }
    
    //std::cerr << "Testing " << args[0] << " ... ";
    // find the test executable
    std::string actualCommand = this->FindTheExecutable(args[1].Value.c_str());
    std::string testCommand = cmSystemTools::ConvertToOutputPath(actualCommand.c_str());
    std::string memcheckcommand = "";

    // continue if we did not find the executable
    if (testCommand == "")
      {
      std::cerr << "Unable to find executable: " <<
        args[1].Value.c_str() << "\n";
      if ( !m_ShowOnly )
        {
        m_TestResults.push_back( cres ); 
        failed.push_back(testname);
        continue;
        }
      }

    // add the arguments
    tm_VectorOfListFileArgs::const_iterator j = args.begin();
    ++j;
    ++j;
    std::vector<const char*> arguments;
    if ( memcheck )
      {
      cmCTest::tm_VectorOfStrings::size_type pp;
      arguments.push_back(m_MemoryTester.c_str());
      memcheckcommand = m_MemoryTester;
      for ( pp = 0; pp < m_MemoryTesterOptionsParsed.size(); pp ++ )
        {
        arguments.push_back(m_MemoryTesterOptionsParsed[pp].c_str());
        memcheckcommand += " ";
        memcheckcommand += cmSystemTools::EscapeSpaces(m_MemoryTesterOptionsParsed[pp].c_str());
        }
      }
    arguments.push_back(actualCommand.c_str());
    for(;j != args.end(); ++j)
      {
      testCommand += " ";
      testCommand += cmSystemTools::EscapeSpaces(j->Value.c_str());
      arguments.push_back(j->Value.c_str());
      }
    arguments.push_back(0);

    /**
     * Run an executable command and put the stdout in output.
     */
    std::string output;
    int retVal = 0;


    if ( m_Verbose )
      {
      std::cout << std::endl << (memcheck?"MemCheck":"Test") << " command: " << testCommand << std::endl;
      if ( memcheck )
        {
        std::cout << "Memory check command: " << memcheckcommand << std::endl;
        }
      }
    if ( olog )
      {
      *olog << cnt << "/" << tmsize 
        << " Test: " << testname.c_str() << std::endl;
      *olog << "Command: ";
      tm_VectorOfStrings::size_type ll;
      for ( ll = 0; ll < arguments.size()-1; ll ++ )
        {
        *olog << "\"" << arguments[ll] << "\" ";
        }
      *olog 
        << std::endl 
        << "Directory: " << it->m_Directory << std::endl 
        << "\"" << testname.c_str() << "\" start time: " 
        << this->CurrentTime() << std::endl
        << "Output:" << std::endl 
        << "----------------------------------------------------------"
        << std::endl;
      }
    int res = 0;
    double clock_start, clock_finish;
    clock_start = cmSystemTools::GetTime();

    if ( !m_ShowOnly )
      {
      res = this->RunTest(arguments, &output, &retVal, olog);
      }

    clock_finish = cmSystemTools::GetTime();

    if ( olog )
      {
      double ttime = clock_finish - clock_start;
      int hours = static_cast<int>(ttime / (60 * 60));
      int minutes = static_cast<int>(ttime / 60) % 60;
      int seconds = static_cast<int>(ttime) % 60;
      char buffer[100];
      sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);
      *olog 
        << "----------------------------------------------------------"
        << std::endl
        << "\"" << testname.c_str() << "\" end time: " 
        << this->CurrentTime() << std::endl
        << "\"" << testname.c_str() << "\" time elapsed: " 
        << buffer << std::endl
        << "----------------------------------------------------------"
        << std::endl << std::endl;
      }

    cres.m_ExecutionTime = (double)(clock_finish - clock_start);
    cres.m_FullCommandLine = testCommand;

    if ( !m_ShowOnly )
      {
      if (res == cmsysProcess_State_Exited && retVal == 0)
        {
        std::cerr <<   "   Passed\n";
        passed.push_back(testname);
        cres.m_Status = cmCTest::COMPLETED;
        }
      else
        {
        cres.m_Status = cmCTest::FAILED;
        if ( res == cmsysProcess_State_Expired )
          {
          std::cerr << "***Timeout\n";
          cres.m_Status = cmCTest::TIMEOUT;
          }
        else if ( res == cmsysProcess_State_Exception )
          {
          std::cerr << "***Exception: ";
          switch ( retVal )
            {
          case cmsysProcess_Exception_Fault:
            std::cerr << "SegFault";
            cres.m_Status = cmCTest::SEGFAULT;
            break;
          case cmsysProcess_Exception_Illegal:
            std::cerr << "Illegal";
            cres.m_Status = cmCTest::ILLEGAL;
            break;
          case cmsysProcess_Exception_Interrupt:
            std::cerr << "Interrupt";
            cres.m_Status = cmCTest::INTERRUPT;
            break;
          case cmsysProcess_Exception_Numerical:
            std::cerr << "Numerical";
            cres.m_Status = cmCTest::NUMERICAL;
            break;
          default:
            std::cerr << "Other";
            cres.m_Status = cmCTest::OTHER_FAULT;
            }
           std::cerr << "\n";
          }
        else if ( res == cmsysProcess_State_Error )
          {
          std::cerr << "***Bad command " << res << "\n";
          cres.m_Status = cmCTest::BAD_COMMAND;
          }
        else
          {
          std::cerr << "***Failed\n";
          }
        failed.push_back(testname);
        }
      if (output != "")
        {
        if (dartStuff.find(output.c_str()))
          {
          std::string dartString = dartStuff.match(1);
          cmSystemTools::ReplaceString(output, dartString.c_str(),"");
          cres.m_RegressionImages = this->GenerateRegressionImages(dartString);
          }
        }
      }
    cres.m_Output = output;
    cres.m_ReturnValue = retVal;
    std::string nwd = it->m_Directory;
    if ( nwd.size() > m_ToplevelPath.size() )
      {
      nwd = "." + nwd.substr(m_ToplevelPath.size(), nwd.npos);
      }
    cmSystemTools::ReplaceString(nwd, "\\", "/");
    cres.m_Path = nwd;
    cres.m_CompletionStatus = "Completed";
    m_TestResults.push_back( cres );
    }

  m_EndTest = this->CurrentTime();
  m_ElapsedTestingTime = cmSystemTools::GetTime() - elapsed_time_start;
  if ( olog )
    {
    *olog << "End testing: " << m_EndTest << std::endl;
    }
  cmSystemTools::ChangeDirectory(current_dir.c_str());
}

bool cmCTest::InitializeMemoryChecking()
{
  // Setup the command
  if ( cmSystemTools::FileExists(m_DartConfiguration["MemoryCheckCommand"].c_str()) )
    {
    m_MemoryTester 
      = cmSystemTools::ConvertToOutputPath(m_DartConfiguration["MemoryCheckCommand"].c_str());
    }
  else if ( cmSystemTools::FileExists(m_DartConfiguration["PurifyCommand"].c_str()) )
    {
    m_MemoryTester 
      = cmSystemTools::ConvertToOutputPath(m_DartConfiguration["PurifyCommand"].c_str());
    }
  else if ( cmSystemTools::FileExists(m_DartConfiguration["ValgrindCommand"].c_str()) )
    {
    m_MemoryTester 
      = cmSystemTools::ConvertToOutputPath(m_DartConfiguration["ValgrindCommand"].c_str());
    }
  else
    {
    std::cerr << "Memory checker (MemoryCheckCommand) not set, or cannot find the specified program." 
      << std::endl;
    return false;
    }

  if ( m_MemoryTester[0] == '\"' && m_MemoryTester[m_MemoryTester.size()-1] == '\"' )
    {
    m_MemoryTester = m_MemoryTester.substr(1, m_MemoryTester.size()-2);
    }

  // Setup the options
  if ( m_DartConfiguration["MemoryCheckCommandOptions"].size() )
    {
    m_MemoryTesterOptions = m_DartConfiguration["MemoryCheckCommandOptions"];
    }
  else if ( m_DartConfiguration["ValgrindCommandOptions"].size() )
    {
    m_MemoryTesterOptions = m_DartConfiguration["ValgrindCommandOptions"];
    }

  m_MemoryTesterOutputFile = m_ToplevelPath + "/Testing/Temporary/MemoryChecker.log";
  m_MemoryTesterOutputFile = cmSystemTools::EscapeSpaces(m_MemoryTesterOutputFile.c_str());

  if ( m_MemoryTester.find("valgrind") != std::string::npos )
    {
    m_MemoryTesterStyle = cmCTest::VALGRIND;
    if ( !m_MemoryTesterOptions.size() )
      {
      m_MemoryTesterOptions = "-q --skin=memcheck --leak-check=yes --show-reachable=yes --workaround-gcc296-bugs=yes --num-callers=100";
      }
    if ( m_DartConfiguration["MemoryCheckSuppressionFile"].size() )
      {
      if ( !cmSystemTools::FileExists(m_DartConfiguration["MemoryCheckSuppressionFile"].c_str()) )
        {
        std::cerr << "Cannot find memory checker suppression file: " 
          << m_DartConfiguration["MemoryCheckSuppressionFile"].c_str() << std::endl;
        return false;
        }
      m_MemoryTesterOptions += " --suppressions=" + cmSystemTools::EscapeSpaces(m_DartConfiguration["MemoryCheckSuppressionFile"].c_str()) + "";
      }
    }
  else if ( m_MemoryTester.find("purify") != std::string::npos )
    {
    m_MemoryTesterStyle = cmCTest::PURIFY;
#ifdef _WIN32
    m_MemoryTesterOptions += " /SAVETEXTDATA=" + m_MemoryTesterOutputFile;
#else
    m_MemoryTesterOptions += " -log-file=" + m_MemoryTesterOutputFile;
#endif
    }
  else if ( m_MemoryTester.find("boundschecker") != std::string::npos )
    {
    m_MemoryTesterStyle = cmCTest::BOUNDS_CHECKER;
    std::cerr << "Bounds checker not yet implemented" << std::endl;
    return false;
    }
  else
    {
    std::cerr << "Do not understand memory checker: " << m_MemoryTester.c_str() << std::endl;
    return false;
    }

  m_MemoryTesterOptionsParsed = cmSystemTools::ParseArguments(m_MemoryTesterOptions.c_str());
  cmCTest::tm_VectorOfStrings::size_type cc;
  for ( cc = 0; cmCTestMemCheckResultStrings[cc]; cc ++ )
    {
    m_MemoryTesterGlobalResults[cc] = 0;
    }
  return true;
}

int cmCTest::TestDirectory(bool memcheck)
{
  m_TestResults.clear();
  std::cout << (memcheck ? "Memory check" : "Test") << " project" << std::endl;
  if ( memcheck )
    {
    if ( !this->InitializeMemoryChecking() )
      {
      return 1;
      }
    }

  if ( memcheck )
    {
    if ( !this->ExecuteCommands(m_CustomPreMemCheck) )
      {
      std::cerr << "Problem executing pre-memcheck command(s)." << std::endl;
      return 1;
      }
    }
  else
    {
    if ( !this->ExecuteCommands(m_CustomPreTest) )
      {
      std::cerr << "Problem executing pre-test command(s)." << std::endl;
      return 1;
      }
    }

  cmCTest::tm_VectorOfStrings passed;
  cmCTest::tm_VectorOfStrings failed;
  int total;

  this->ProcessDirectory(passed, failed, memcheck);

  total = int(passed.size()) + int(failed.size());

  if (total == 0)
    {
    if ( !m_ShowOnly )
      {
      std::cerr << "No tests were found!!!\n";
      }
    }
  else
    {
    if (m_Verbose && passed.size() && 
      (m_UseIncludeRegExp || m_UseExcludeRegExp)) 
      {
      std::cerr << "\nThe following tests passed:\n";
      for(cmCTest::tm_VectorOfStrings::iterator j = passed.begin();
        j != passed.end(); ++j)
        {   
        std::cerr << "\t" << *j << "\n";
        }
      }

    float percent = float(passed.size()) * 100.0f / total;
    if ( failed.size() > 0 &&  percent > 99)
      {
      percent = 99;
      }
    fprintf(stderr,"\n%.0f%% tests passed, %i tests failed out of %i\n",
      percent, int(failed.size()), total);

    if (failed.size()) 
      {
      std::ofstream ofs;

      std::cerr << "\nThe following tests FAILED:\n";
      this->OpenOutputFile("Temporary", "LastTestsFailed.log", ofs);

      std::vector<cmCTest::cmCTestTestResult>::iterator ftit;
      for(ftit = m_TestResults.begin();
        ftit != m_TestResults.end(); ++ftit)
        {
        if ( ftit->m_Status != cmCTest::COMPLETED )
          {
          ofs << ftit->m_TestCount << ":" << ftit->m_Name << std::endl;
          fprintf(stderr, "\t%3d - %s (%s)\n", ftit->m_TestCount, ftit->m_Name.c_str(),
            this->GetTestStatus(ftit->m_Status));
          }
        }

      }
    }

  if ( m_DartMode )
    {
    std::ofstream xmlfile;
    if( !this->OpenOutputFile(m_CurrentTag, 
        (memcheck ? (m_CompatibilityMode?"Purify.xml":"DynamicAnalysis.xml") : "Test.xml"), xmlfile) )
      {
      std::cerr << "Cannot create " << (memcheck ? "memory check" : "testing")
        << " XML file" << std::endl;
      return 1;
      }
    if ( memcheck )
      {
      this->GenerateDartMemCheckOutput(xmlfile);
      }
    else
      {
      this->GenerateDartTestOutput(xmlfile);
      }
    }

  if ( memcheck )
    {
    if ( !this->ExecuteCommands(m_CustomPostMemCheck) )
      {
      std::cerr << "Problem executing post-memcheck command(s)." << std::endl;
      return 1;
      }
    }
  else
    {
    if ( !this->ExecuteCommands(m_CustomPostTest) )
      {
      std::cerr << "Problem executing post-test command(s)." << std::endl;
      return 1;
      }
    }

  return int(failed.size());
}

int cmCTest::SubmitResults()
{
  std::ofstream ofs;
  this->OpenOutputFile("Temporary", "LastSubmit.log", ofs);

  cmCTest::tm_VectorOfStrings files;
  std::string prefix = this->GetSubmitResultsPrefix();
  // TODO:
  // Check if test is enabled
  if ( this->CTestFileExists("Update.xml") )
    {
    files.push_back("Update.xml");
    }
  if ( this->CTestFileExists("Configure.xml") )
    {
    files.push_back("Configure.xml");
    }
  if ( this->CTestFileExists("Build.xml") )
    {
    files.push_back("Build.xml");
    }
  if ( this->CTestFileExists("Test.xml") )
    {
    files.push_back("Test.xml");
    }
  if ( this->CTestFileExists("Coverage.xml") )
    {
    files.push_back("Coverage.xml");
    cmCTest::tm_VectorOfStrings gfiles;
    std::string gpath = m_ToplevelPath + "/Testing/" + m_CurrentTag;
    std::string::size_type glen = gpath.size() + 1;
    gpath = gpath + "/CoverageLog*";
    //std::cout << "Globbing for: " << gpath.c_str() << std::endl;
    if ( cmSystemTools::SimpleGlob(gpath, gfiles, 1) )
      {
      size_t cc;
      for ( cc = 0; cc < gfiles.size(); cc ++ )
        {
        gfiles[cc] = gfiles[cc].substr(glen);
        //std::cout << "Glob file: " << gfiles[cc].c_str() << std::endl;
        files.push_back(gfiles[cc]);
        }
      }
    else
      {
      std::cerr << "Problem globbing" << std::endl;
      }
    }
  if ( this->CTestFileExists("DynamicAnalysis.xml") )
    {
    files.push_back("DynamicAnalysis.xml");
    }
  if ( this->CTestFileExists("Purify.xml") )
    {
    files.push_back("Purify.xml");
    }
  if ( this->CTestFileExists("Notes.xml") )
    {
    files.push_back("Notes.xml");
    }

  if ( ofs )
    {
    ofs << "Upload files:" << std::endl;
    int cnt = 0;
    cmCTest::tm_VectorOfStrings::iterator it;
    for ( it = files.begin(); it != files.end(); ++ it )
      {
      ofs << cnt << "\t" << it->c_str() << std::endl;
      cnt ++;
      }
    }
  std::cout << "Submit files (using " << m_DartConfiguration["DropMethod"] << ")"
    << std::endl;
  cmCTestSubmit submit;
  submit.SetVerbose(m_Verbose);
  submit.SetLogFile(&ofs);
  if ( m_DartConfiguration["DropMethod"] == "" ||
    m_DartConfiguration["DropMethod"] ==  "ftp" )
    {
    ofs << "Using drop method: FTP" << std::endl;
    std::cout << "  Using FTP submit method" << std::endl;
    std::string url = "ftp://";
    url += cmCTest::MakeURLSafe(m_DartConfiguration["DropSiteUser"]) + ":" + 
      cmCTest::MakeURLSafe(m_DartConfiguration["DropSitePassword"]) + "@" + 
      m_DartConfiguration["DropSite"] + 
      cmCTest::MakeURLSafe(m_DartConfiguration["DropLocation"]);
    if ( !submit.SubmitUsingFTP(m_ToplevelPath+"/Testing/"+m_CurrentTag, 
        files, prefix, url) )
      {
      std::cerr << "  Problems when submitting via FTP" << std::endl;
      ofs << "  Problems when submitting via FTP" << std::endl;
      return 0;
      }
    if ( !submit.TriggerUsingHTTP(files, prefix, m_DartConfiguration["TriggerSite"]) )
      {
      std::cerr << "  Problems when triggering via HTTP" << std::endl;
      ofs << "  Problems when triggering via HTTP" << std::endl;
      return 0;
      }
    std::cout << "  Submission successfull" << std::endl;
    ofs << "  Submission succesfull" << std::endl;
    return 1;
    }
  else if ( m_DartConfiguration["DropMethod"] == "http" )
    {
    ofs << "Using drop method: HTTP" << std::endl;
    std::cout << "  Using HTTP submit method" << std::endl;
    std::string url = "http://";
    if ( m_DartConfiguration["DropSiteUser"].size() > 0 )
      {
      url += m_DartConfiguration["DropSiteUser"];
      if ( m_DartConfiguration["DropSitePassword"].size() > 0 )
        {
        url += ":" + m_DartConfiguration["DropSitePassword"];
        }
      url += "@";
      }
    url += m_DartConfiguration["DropSite"] + m_DartConfiguration["DropLocation"];
    if ( !submit.SubmitUsingHTTP(m_ToplevelPath+"/Testing/"+m_CurrentTag, files, prefix, url) )
      {
      std::cerr << "  Problems when submitting via HTTP" << std::endl;
      ofs << "  Problems when submitting via HTTP" << std::endl;
      return 0;
      }
    if ( !submit.TriggerUsingHTTP(files, prefix, m_DartConfiguration["TriggerSite"]) )
      {
      std::cerr << "  Problems when triggering via HTTP" << std::endl;
      ofs << "  Problems when triggering via HTTP" << std::endl;
      return 0;
      }
    std::cout << "  Submission successfull" << std::endl;
    ofs << "  Submission succesfull" << std::endl;
    return 1;
    }
  else
    {
    std::string url;
    if ( m_DartConfiguration["DropSiteUser"].size() > 0 )
      {
      url += m_DartConfiguration["DropSiteUser"] + "@";
      }
    url += m_DartConfiguration["DropSite"] + ":" + m_DartConfiguration["DropLocation"];
    
    if ( !submit.SubmitUsingSCP(m_DartConfiguration["ScpCommand"],
        m_ToplevelPath+"/Testing/"+m_CurrentTag, files, prefix, url) )
      {
      std::cerr << "  Problems when submitting via SCP" << std::endl;
      ofs << "  Problems when submitting via SCP" << std::endl;
      return 0;
      }
    std::cout << "  Submission successfull" << std::endl;
    ofs << "  Submission succesfull" << std::endl;
    }

  return 0;
}

bool cmCTest::CTestFileExists(const std::string& filename)
{
  std::string testingDir = m_ToplevelPath + "/Testing/" + m_CurrentTag + "/" +
    filename;
  return cmSystemTools::FileExists(testingDir.c_str());
}

std::string cmCTest::GetSubmitResultsPrefix()
{
  std::string name = m_DartConfiguration["Site"] +
    "___" + m_DartConfiguration["BuildName"] +
    "___" + m_CurrentTag + "-" +
    this->GetTestModelString() + "___XML___";
  return name;
}

void cmCTest::GenerateDartMemCheckOutput(std::ostream& os)
{
  if ( !m_DartMode )
    {
    return;
    }

  this->StartXML(os);
  if ( m_CompatibilityMode )
    {
    os << "<Purify>" << std::endl;
    }
  else
    {
    os << "<DynamicAnalysis Checker=\"";
    switch ( m_MemoryTesterStyle )
      {
    case cmCTest::VALGRIND:
      os << "Valgrind";
      break;
    case cmCTest::PURIFY:
      os << "Purify";
      break;
    case cmCTest::BOUNDS_CHECKER:
      os << "BoundsChecker";
      break;
    default:
      os << "Unknown";
      }
    os << "\">" << std::endl;
    }
  os << "\t<StartDateTime>" << m_StartTest << "</StartDateTime>\n"
    << "\t<TestList>\n";
  tm_TestResultsVector::size_type cc;
  for ( cc = 0; cc < m_TestResults.size(); cc ++ )
    {
    cmCTestTestResult *result = &m_TestResults[cc];
    os << "\t\t<Test>" << this->MakeXMLSafe(result->m_Path) 
      << "/" << this->MakeXMLSafe(result->m_Name)
      << "</Test>" << std::endl;
    }
  os << "\t</TestList>\n";
  std::cout << "-- Processing memory checking output: ";
  unsigned int total = m_TestResults.size();
  unsigned int step = total / 10;
  unsigned int current = 0;
  for ( cc = 0; cc < m_TestResults.size(); cc ++ )
    {
    cmCTestTestResult *result = &m_TestResults[cc];
    std::string memcheckstr;
    int memcheckresults[cmCTest::NO_MEMORY_FAULT];
    int kk;
    bool res = this->ProcessMemCheckOutput(result->m_Output, memcheckstr, memcheckresults);
    if ( res && result->m_Status == cmCTest::COMPLETED )
      {
      continue;
      }
    os << "\t<Test Status=\"";
    if ( result->m_Status == cmCTest::COMPLETED )
      {
      os << "passed";
      }
    else if ( result->m_Status == cmCTest::NOT_RUN )
      {
      os << "notrun";
      }
    else
      {
      os << "failed";
      }
    os << "\">\n"
      << "\t\t<Name>" << this->MakeXMLSafe(result->m_Name) << "</Name>\n"
      << "\t\t<Path>" << this->MakeXMLSafe(result->m_Path) << "</Path>\n"
      << "\t\t<FullName>" << this->MakeXMLSafe(result->m_Path) 
      << "/" << this->MakeXMLSafe(result->m_Name) << "</FullName>\n"
      << "\t\t<FullCommandLine>" 
      << this->MakeXMLSafe(result->m_FullCommandLine) 
      << "</FullCommandLine>\n"
      << "\t\t<Results>" << std::endl;
    if ( m_CompatibilityMode )
      {
      for ( kk = 0; cmCTestMemCheckResultStrings[kk]; kk ++ )
        {
        os << "\t\t\t<" << cmCTestMemCheckResultStrings[kk] << ">"
          << memcheckresults[kk] 
          << "</" << cmCTestMemCheckResultStrings[kk] << ">" << std::endl;
        m_MemoryTesterGlobalResults[kk] += memcheckresults[kk];
        }
      }
    else
      {
      for ( kk = 0; cmCTestMemCheckResultLongStrings[kk]; kk ++ )
        {
        if ( memcheckresults[kk] )
          {
          os << "\t\t\t<Defect type=\"" << cmCTestMemCheckResultLongStrings[kk] << "\">"
            << memcheckresults[kk] 
            << "</Defect>" << std::endl;
          }
        m_MemoryTesterGlobalResults[kk] += memcheckresults[kk];
        }
      }
    os 
      << "\t\t</Results>\n"
      << "\t<Log>\n" << memcheckstr << std::endl
      << "\t</Log>\n"
      << "\t</Test>" << std::endl;
    if ( current < cc )
      {
      std::cout << "#";
      std::cout.flush();
      current += step;
      }
    }
  std::cout << std::endl;
  std::cerr << "Memory checking results:" << std::endl;
  os << "\t<DefectList>" << std::endl;
  for ( cc = 0; cmCTestMemCheckResultStrings[cc]; cc ++ )
    {
    if ( m_MemoryTesterGlobalResults[cc] )
      {
      std::cerr.width(35);
      std::cerr << cmCTestMemCheckResultLongStrings[cc] << " - " 
        << m_MemoryTesterGlobalResults[cc] << std::endl;
      if ( !m_CompatibilityMode )
        {
        os << "\t\t<Defect Type=\"" << cmCTestMemCheckResultLongStrings[cc] << "\"/>" << std::endl;
        }
      }
    }
  os << "\t</DefectList>" << std::endl;

  os << "\t<EndDateTime>" << m_EndTest << "</EndDateTime>" << std::endl;
  os << "<ElapsedMinutes>" 
     << static_cast<int>(m_ElapsedTestingTime/6)/10.0 
     << "</ElapsedMinutes>\n";
  
  if ( m_CompatibilityMode )
    {
    os << "</Purify>" << std::endl;
    }
  else
    {
    os << "</DynamicAnalysis>" << std::endl;
    }
  this->EndXML(os);


}

void cmCTest::GenerateDartTestOutput(std::ostream& os)
{
  if ( !m_DartMode )
    {
    return;
    }

  this->StartXML(os);
  os << "<Testing>\n"
    << "\t<StartDateTime>" << m_StartTest << "</StartDateTime>\n"
    << "\t<TestList>\n";
  tm_TestResultsVector::size_type cc;
  for ( cc = 0; cc < m_TestResults.size(); cc ++ )
    {
    cmCTestTestResult *result = &m_TestResults[cc];
    os << "\t\t<Test>" << this->MakeXMLSafe(result->m_Path) 
      << "/" << this->MakeXMLSafe(result->m_Name)
      << "</Test>" << std::endl;
    }
  os << "\t</TestList>\n";
  for ( cc = 0; cc < m_TestResults.size(); cc ++ )
    {
    cmCTestTestResult *result = &m_TestResults[cc];
    os << "\t<Test Status=\"";
    if ( result->m_Status == cmCTest::COMPLETED )
      {
      os << "passed";
      }
    else if ( result->m_Status == cmCTest::NOT_RUN )
      {
      os << "notrun";
      }
    else
      {
      os << "failed";
      }
    os << "\">\n"
      << "\t\t<Name>" << this->MakeXMLSafe(result->m_Name) << "</Name>\n"
      << "\t\t<Path>" << this->MakeXMLSafe(result->m_Path) << "</Path>\n"
      << "\t\t<FullName>" << this->MakeXMLSafe(result->m_Path) 
      << "/" << this->MakeXMLSafe(result->m_Name) << "</FullName>\n"
      << "\t\t<FullCommandLine>" 
      << this->MakeXMLSafe(result->m_FullCommandLine) 
      << "</FullCommandLine>\n"
      << "\t\t<Results>" << std::endl;
    if ( result->m_Status != cmCTest::NOT_RUN )
      {
      if ( result->m_Status != cmCTest::COMPLETED || result->m_ReturnValue )
        {
        os << "\t\t\t<NamedMeasurement type=\"text/string\" name=\"Exit Code\"><Value>"
          << this->GetTestStatus(result->m_Status) << "</Value></NamedMeasurement>\n"
          << "\t\t\t<NamedMeasurement type=\"text/string\" name=\"Exit Value\"><Value>"
          << result->m_ReturnValue << "</Value></NamedMeasurement>" << std::endl;
        }
      os << result->m_RegressionImages;
      os << "\t\t\t<NamedMeasurement type=\"numeric/double\" "
        << "name=\"Execution Time\"><Value>"
        << result->m_ExecutionTime << "</Value></NamedMeasurement>\n";
      os 
        << "\t\t\t<NamedMeasurement type=\"text/string\" "
        << "name=\"Completion Status\"><Value>"
        << result->m_CompletionStatus << "</Value></NamedMeasurement>\n";
      }
    os 
      << "\t\t\t<Measurement>\n"
      << "\t\t\t\t<Value>";
    size_t truncate = result->m_Output.size();
    if ( result->m_Status == cmCTest::COMPLETED )
      {
      if ( result->m_Output.size() > m_MaximumPassedTestResultSize )
        {
        truncate = m_MaximumPassedTestResultSize;
        }
      }
    else
      {
      if ( result->m_Output.size() > m_MaximumFailedTestResultSize )
        {
        truncate = m_MaximumFailedTestResultSize;
        }
      }
    os << this->MakeXMLSafe(result->m_Output.substr(0, truncate));
    if ( truncate < result->m_Output.size() )
      {
      os << "...\n\nThe output was stirpped because it excedes maximum allowed size: "
        << truncate << std::endl;
      }
    os
      << "</Value>\n"
      << "\t\t\t</Measurement>\n"
      << "\t\t</Results>\n"
      << "\t</Test>" << std::endl;
    }

  os << "\t<EndDateTime>" << m_EndTest << "</EndDateTime>\n"
     << "<ElapsedMinutes>" 
     << static_cast<int>(m_ElapsedTestingTime/6)/10.0
     << "</ElapsedMinutes>"
    << "</Testing>" << std::endl;
  this->EndXML(os);
}

int cmCTest::ProcessTests()
{
  int res = 0;
  bool notest = true;
  int cc;
  int update_count = 0;

  for ( cc = 0; cc < LAST_TEST; cc ++ )
    {
    if ( m_Tests[cc] )
      {
      notest = false;
      break;
      }
    }
  if ( m_Tests[UPDATE_TEST] || m_Tests[ALL_TEST] )
    {
    update_count = this->UpdateHandler->UpdateDirectory(this); 
    if ( update_count < 0 )
      {
      res |= cmCTest::UPDATE_ERRORS;
      }
    }
  if ( m_TestModel == cmCTest::CONTINUOUS && !update_count )
    {
    return 0;
    }
  if ( m_Tests[CONFIGURE_TEST] || m_Tests[ALL_TEST] )
    {
    if (this->ConfigureHandler->ConfigureDirectory(this))
      {
      res |= cmCTest::CONFIGURE_ERRORS;
      }
    }
  if ( m_Tests[BUILD_TEST] || m_Tests[ALL_TEST] )
    {
    this->UpdateCTestConfiguration();
    if (this->BuildDirectory())
      {
      res |= cmCTest::BUILD_ERRORS;
      }
    }
  if ( m_Tests[TEST_TEST] || m_Tests[ALL_TEST] || notest )
    {
    this->UpdateCTestConfiguration();
    if (this->TestDirectory(false))
      {
      res |= cmCTest::TEST_ERRORS;
      }
    }
  if ( m_Tests[COVERAGE_TEST] || m_Tests[ALL_TEST] )
    {
    this->UpdateCTestConfiguration();
    this->CoverageDirectory();
    }
  if ( m_Tests[MEMCHECK_TEST] || m_Tests[ALL_TEST] )
    {
    this->UpdateCTestConfiguration();
    if (this->TestDirectory(true))
      {
      res |= cmCTest::MEMORY_ERRORS;
      }
    }
  if ( !notest )
    {
    std::string notes_dir = m_ToplevelPath + "/Testing/Notes";
    if ( cmSystemTools::FileIsDirectory(notes_dir.c_str()) )
      {
      cmsys::Directory d;
      d.Load(notes_dir.c_str());
      unsigned long kk;
      for ( kk = 0; kk < d.GetNumberOfFiles(); kk ++ )
        {
        const char* file = d.GetFile(kk);
        std::string fullname = notes_dir + "/" + file;
        if ( cmSystemTools::FileExists(fullname.c_str()) &&
          !cmSystemTools::FileIsDirectory(fullname.c_str()) )
          {
          if ( m_NotesFiles.size() > 0 )
            {
            m_NotesFiles += ";";
            }
          m_NotesFiles += fullname;
          m_Tests[NOTES_TEST] = 1;
          }
        }
      }
    }
  if ( m_Tests[NOTES_TEST] || m_Tests[ALL_TEST] )
    {
    this->UpdateCTestConfiguration();
    if ( m_NotesFiles.size() )
      {
      this->GenerateNotesFile(m_NotesFiles.c_str());
      }
    }
  if ( m_Tests[SUBMIT_TEST] || m_Tests[ALL_TEST] )
    {
    this->UpdateCTestConfiguration();
    this->SubmitResults();
    }
  return res;
}

std::string cmCTest::GetTestModelString()
{
  switch ( m_TestModel )
    {
  case cmCTest::NIGHTLY:
    return "Nightly";
  case cmCTest::CONTINUOUS:
    return "Continuous";
    }
  return "Experimental";
}

int cmCTest::GetTestModelFromString(const char* str)
{
  if ( !str )
    {
    return cmCTest::EXPERIMENTAL;
    }
  std::string rstr = cmSystemTools::LowerCase(str);
  if ( strncmp(rstr.c_str(), "cont", 4) == 0 )
    {
    return cmCTest::CONTINUOUS;
    }
  if ( strncmp(rstr.c_str(), "nigh", 4) == 0 )
    {
    return cmCTest::NIGHTLY;
    }
  return cmCTest::EXPERIMENTAL;
}

#define SPACE_REGEX "[ \t\r\n]"

std::string cmCTest::GenerateRegressionImages(const std::string& xml)
{
  cmsys::RegularExpression twoattributes(
    "<DartMeasurement" 
    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
    SPACE_REGEX "*>([^<]*)</DartMeasurement>");
  cmsys::RegularExpression threeattributes(
    "<DartMeasurement" 
    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
    SPACE_REGEX "*>([^<]*)</DartMeasurement>");
  cmsys::RegularExpression fourattributes(
    "<DartMeasurement" 
    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
    SPACE_REGEX "*>([^<]*)</DartMeasurement>");
  cmsys::RegularExpression measurementfile(
    "<DartMeasurementFile" 
    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
    SPACE_REGEX "*>([^<]*)</DartMeasurementFile>");

  cmOStringStream ostr;
  bool done = false;
  std::string cxml = xml;
  while ( ! done )
    {
    if ( twoattributes.find(cxml) )
      {
      ostr
        << "\t\t\t<NamedMeasurement" 
        << " " << twoattributes.match(1) << "=\"" << twoattributes.match(2) << "\""
        << " " << twoattributes.match(3) << "=\"" << twoattributes.match(4) << "\""
        << "><Value>" << twoattributes.match(5) 
        << "</Value></NamedMeasurement>" 
        << std::endl;
      cxml.erase(twoattributes.start(), twoattributes.end() - twoattributes.start());
      }
    else if ( threeattributes.find(cxml) )
      {
      ostr
        << "\t\t\t<NamedMeasurement" 
        << " " << threeattributes.match(1) << "=\"" << threeattributes.match(2) << "\""
        << " " << threeattributes.match(3) << "=\"" << threeattributes.match(4) << "\""
        << " " << threeattributes.match(5) << "=\"" << threeattributes.match(6) << "\""
        << "><Value>" << threeattributes.match(7) 
        << "</Value></NamedMeasurement>" 
        << std::endl;
      cxml.erase(threeattributes.start(), threeattributes.end() - threeattributes.start());
      }
    else if ( fourattributes.find(cxml) )
      {
      ostr
        << "\t\t\t<NamedMeasurement" 
        << " " << fourattributes.match(1) << "=\"" << fourattributes.match(2) << "\""
        << " " << fourattributes.match(3) << "=\"" << fourattributes.match(4) << "\""
        << " " << fourattributes.match(5) << "=\"" << fourattributes.match(6) << "\""
        << " " << fourattributes.match(7) << "=\"" << fourattributes.match(8) << "\""
        << "><Value>" << fourattributes.match(9) 
        << "</Value></NamedMeasurement>" 
        << std::endl;
      cxml.erase(fourattributes.start(), fourattributes.end() - fourattributes.start());
      }
    else if ( measurementfile.find(cxml) )
      {
      const std::string& filename = ::CleanString(measurementfile.match(5));
      if ( cmSystemTools::FileExists(filename.c_str()) )
        {
        long len = cmSystemTools::FileLength(filename.c_str());
        if ( len == 0 )
          {
          std::string k1 = measurementfile.match(1);
          std::string v1 = measurementfile.match(2);
          std::string k2 = measurementfile.match(3);
          std::string v2 = measurementfile.match(4);
          if ( cmSystemTools::LowerCase(k1) == "type" )
            {
            v1 = "text/string";
            }
          if ( cmSystemTools::LowerCase(k2) == "type" )
            {
            v2 = "text/string";
            }          
          
          ostr
            << "\t\t\t<NamedMeasurement" 
            << " " << k1 << "=\"" << v1 << "\""
            << " " << k2 << "=\"" << v2 << "\""
            << " encoding=\"none\""
            << "><Value>Image " << filename.c_str() 
            << " is empty</Value></NamedMeasurement>";
          }
        else
          {
          std::ifstream ifs(filename.c_str(), std::ios::in 
#ifdef _WIN32
                            | std::ios::binary
#endif
            );
          unsigned char *file_buffer = new unsigned char [ len + 1 ];
          ifs.read(reinterpret_cast<char*>(file_buffer), len);
          unsigned char *encoded_buffer = new unsigned char [ static_cast<int>(len * 1.5 + 5) ];
          
          unsigned long rlen = cmsysBase64_Encode(file_buffer, len, encoded_buffer, 1);
          unsigned long cc;
          
          ostr
            << "\t\t\t<NamedMeasurement" 
          << " " << measurementfile.match(1) << "=\"" << measurementfile.match(2) << "\""
            << " " << measurementfile.match(3) << "=\"" << measurementfile.match(4) << "\""
            << " encoding=\"base64\""
            << ">" << std::endl << "\t\t\t\t<Value>";
          for ( cc = 0; cc < rlen; cc ++ )
            {
            ostr << encoded_buffer[cc];
            if ( cc % 60 == 0 && cc )
              {
              ostr << std::endl;
              }
            }
          ostr
            << "</Value>" << std::endl << "\t\t\t</NamedMeasurement>" 
            << std::endl;
          delete [] file_buffer;
          delete [] encoded_buffer;
          }
        }
      else
        {
        int idx = 4;
        if ( measurementfile.match(1) == "name" )
          {
          idx = 2;
          }
        ostr
          << "\t\t\t<NamedMeasurement" 
          << " name=\"" << measurementfile.match(idx) << "\""
          << " text=\"text/string\""
          << "><Value>File " << filename.c_str() << " not found</Value></NamedMeasurement>" 
          << std::endl;
        std::cout << "File \"" << filename.c_str() << "\" not found." << std::endl;
        }
      cxml.erase(measurementfile.start(), measurementfile.end() - measurementfile.start());
      }
    else
      {
      done = true;
      }
    }
  return ostr.str();
}

int cmCTest::RunMakeCommand(const char* command, std::string* output,
  int* retVal, const char* dir, bool verbose, int timeout, std::ofstream& ofs)
{
  std::vector<cmStdString> args = cmSystemTools::ParseArguments(command);

  if(args.size() < 1)
    {
    return false;
    }

  std::vector<const char*> argv;
  for(std::vector<cmStdString>::const_iterator a = args.begin();
    a != args.end(); ++a)
    {
    argv.push_back(a->c_str());
    }
  argv.push_back(0);

  if ( output )
    {
    *output = "";
    }

  cmsysProcess* cp = cmsysProcess_New();
  cmsysProcess_SetCommand(cp, &*argv.begin());
  cmsysProcess_SetWorkingDirectory(cp, dir);
  cmsysProcess_SetOption(cp, cmsysProcess_Option_HideWindow, 1);
  cmsysProcess_SetTimeout(cp, timeout);
  cmsysProcess_Execute(cp);

  std::string::size_type tick = 0;
  std::string::size_type tick_len = 1024;
  std::string::size_type tick_line_len = 50;

  char* data;
  int length;
  if ( !verbose )
    {
    std::cout << "   Each . represents " << tick_len << " bytes of output" << std::endl;
    std::cout << "    " << std::flush;
    }
  while(cmsysProcess_WaitForData(cp, &data, &length, 0))
    {
    if ( output )
      {
      for(int cc =0; cc < length; ++cc)
        {
        if(data[cc] == 0)
          {
          data[cc] = '\n';
          }
        }

      output->append(data, length);
      if ( !verbose )
        {
        while ( output->size() > (tick * tick_len) )
          {
          tick ++;
          std::cout << "." << std::flush;
          if ( tick % tick_line_len == 0 && tick > 0 )
            {
            std::cout << "  Size: ";
            std::cout << int((output->size() / 1024.0) + 1) << "K" << std::endl;
            std::cout << "    " << std::flush;
            }
          }
        }
      }
    if(verbose)
      {
      std::cout.write(data, length);
      std::cout.flush();
      }
    if ( ofs )
      {
      ofs.write(data, length);
      ofs.flush();
      }
    }
  std::cout << " Size of output: ";
  std::cout << int(output->size() / 1024.0) << "K" << std::endl;

  cmsysProcess_WaitForExit(cp, 0);

  int result = cmsysProcess_GetState(cp);

  if(result == cmsysProcess_State_Exited)
    {
    *retVal = cmsysProcess_GetExitValue(cp);
    }
  else if(result == cmsysProcess_State_Exception)
    {
    *retVal = cmsysProcess_GetExitException(cp);
    std::cout << "There was an exception: " << *retVal << std::endl;
    }
  else if(result == cmsysProcess_State_Expired)
    {
    std::cout << "There was a timeout" << std::endl;
    } 
  else if(result == cmsysProcess_State_Error)
    {
    *output += "\n*** ERROR executing: ";
    *output += cmsysProcess_GetErrorString(cp);
    }

  cmsysProcess_Delete(cp);

  return result;
}

int cmCTest::RunTest(std::vector<const char*> argv, std::string* output, int *retVal,
  std::ostream* log)
{
  if(cmSystemTools::SameFile(argv[0], m_CTestSelf.c_str()) && !m_ForceNewCTestProcess)
    {
    cmCTest inst;
    inst.m_ConfigType = m_ConfigType;
    inst.m_TimeOut = m_TimeOut;
    std::vector<std::string> args;
    for(unsigned int i =0; i < argv.size(); ++i)
      {
      if(argv[i])
        {
        args.push_back(argv[i]);
        }
      }
    if ( *log )
      {
      *log << "* Run internal CTest" << std::endl;
      }
    std::string oldpath = cmSystemTools::GetCurrentWorkingDirectory();
    
    *retVal = inst.Run(args, output);
    if ( *log )
      {
      *log << output->c_str();
      }
    cmSystemTools::ChangeDirectory(oldpath.c_str());
    
    if(m_Verbose)
      {
      std::cout << "Internal cmCTest object used to run test.\n";
      std::cout <<  *output << "\n";
      }
    return cmsysProcess_State_Exited;
    }
  std::vector<char> tempOutput;
  if ( output )
    {
    *output = "";
    }

  cmsysProcess* cp = cmsysProcess_New();
  cmsysProcess_SetCommand(cp, &*argv.begin());
  //  std::cout << "Command is: " << argv[0] << std::endl;
  if(cmSystemTools::GetRunCommandHideConsole())
    {
    cmsysProcess_SetOption(cp, cmsysProcess_Option_HideWindow, 1);
    }
  cmsysProcess_SetTimeout(cp, m_TimeOut);
  cmsysProcess_Execute(cp);

  char* data;
  int length;
  while(cmsysProcess_WaitForData(cp, &data, &length, 0))
    {
    if ( output )
      {
      tempOutput.insert(tempOutput.end(), data, data+length);
      }
    if ( m_Verbose )
      {
      std::cout.write(data, length);
      std::cout.flush();
      }
    if ( log )
      {
      log->write(data, length);
      log->flush();
      }
    }

  cmsysProcess_WaitForExit(cp, 0);
  if(output)
    {
    output->append(&*tempOutput.begin(), tempOutput.size());
    }
  if ( m_Verbose )
    {
    std::cout << "-- Process completed" << std::endl;
    }

  int result = cmsysProcess_GetState(cp);

  if(result == cmsysProcess_State_Exited)
    {
    *retVal = cmsysProcess_GetExitValue(cp);
    }
  else if(result == cmsysProcess_State_Exception)
    {
    *retVal = cmsysProcess_GetExitException(cp);
    std::string outerr = "\n*** Exception executing: ";
    outerr += cmsysProcess_GetExceptionString(cp);
    *output += outerr;
    if ( m_Verbose )
      {
      std::cout << outerr.c_str() << "\n";
      std::cout.flush();
      }
    }
  else if(result == cmsysProcess_State_Error)
    {
    std::string outerr = "\n*** ERROR executing: ";
    outerr += cmsysProcess_GetErrorString(cp);
    *output += outerr;
    if ( m_Verbose )
      {
      std::cout << outerr.c_str() << "\n";
      std::cout.flush();
      }
    }
  cmsysProcess_Delete(cp);

  return result;
}

const char* cmCTest::GetTestStatus(int status)
{
  static const char statuses[][100] = {
    "Not Run",
    "Timeout",
    "SEGFAULT",
    "ILLEGAL",
    "INTERRUPT",
    "NUMERICAL",
    "OTHER_FAULT",
    "Failed",
    "BAD_COMMAND",
    "Completed"
  };

  if ( status < cmCTest::NOT_RUN || status > cmCTest::COMPLETED )
    {
    return "No Status";
    }
  return statuses[status];
}

void cmCTest::StartXML(std::ostream& ostr)
{
  ostr << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
    << "\" BuildStamp=\"" << m_CurrentTag << "-"
    << this->GetTestModelString() << "\" Name=\""
    << m_DartConfiguration["Site"] << "\" Generator=\"ctest-" << CMake_VERSION_FULL
    << "\">" << std::endl;
}

void cmCTest::EndXML(std::ostream& ostr)
{
  ostr << "</Site>" << std::endl;
}

bool cmCTest::ProcessMemCheckPurifyOutput(const std::string&, std::string& log, 
  int* results)
{
  if ( !cmSystemTools::FileExists(m_MemoryTesterOutputFile.c_str()) )
    {
    log = "Cannot find Purify output file: " + m_MemoryTesterOutputFile;
    std::cerr << log.c_str() << std::endl;
    return false;
    }

  std::ifstream ifs(m_MemoryTesterOutputFile.c_str());
  if ( !ifs )
    {
    log = "Cannot read Purify output file: " + m_MemoryTesterOutputFile;
    std::cerr << log.c_str() << std::endl;
    return false;
    }

  cmOStringStream ostr;
  log = "";

  cmsys::RegularExpression pfW("^\\[[WEI]\\] ([A-Z][A-Z][A-Z][A-Z]*): ");

  int defects = 0;

  std::string line;
  while ( cmSystemTools::GetLineFromStream(ifs, line) )
    {
    int failure = cmCTest::NO_MEMORY_FAULT;
    if ( pfW.find(line) )
      {
      int cc;
      for ( cc = 0; cc < cmCTest::NO_MEMORY_FAULT; cc ++ )
        {
        if ( pfW.match(1) == cmCTestMemCheckResultStrings[cc] )
          {
          failure = cc;
          break;
          }
        }
      if ( cc == cmCTest::NO_MEMORY_FAULT )
        {
        std::cerr<< "Unknown Purify memory fault: " << pfW.match(1) << std::endl;
        ostr << "*** Unknown Purify memory fault: " << pfW.match(1) << std::endl;
        }
      }
    if ( failure != NO_MEMORY_FAULT )
      {
      ostr << "<b>" << cmCTestMemCheckResultStrings[failure] << "</b> ";
      results[failure] ++;
      defects ++;
      }
    ostr << cmCTest::MakeXMLSafe(line) << std::endl;
    }

  log = ostr.str();
  if ( defects )
    {
    return false;
    }
  return true;
}

bool cmCTest::ProcessMemCheckValgrindOutput(const std::string& str, std::string& log, 
  int* results)
{
  std::vector<cmStdString> lines;
  cmSystemTools::Split(str.c_str(), lines);
 
  std::string::size_type cc;

  cmOStringStream ostr;
  log = "";

  int defects = 0;

  cmsys::RegularExpression valgrindLine("^==[0-9][0-9]*==");

  cmsys::RegularExpression vgFIM(
    "== .*Invalid free\\(\\) / delete / delete\\[\\]");
  cmsys::RegularExpression vgFMM(
    "== .*Mismatched free\\(\\) / delete / delete \\[\\]");
  cmsys::RegularExpression vgMLK(
    "== .*[0-9][0-9]* bytes in [0-9][0-9]* blocks are definitely lost"
    " in loss record [0-9][0-9]* of [0-9]");
  cmsys::RegularExpression vgPAR(
    "== .*Syscall param .* contains unaddressable byte\\(s\\)");
  cmsys::RegularExpression vgMPK1(
    "== .*[0-9][0-9]* bytes in [0-9][0-9]* blocks are possibly lost in"
    " loss record [0-9][0-9]* of [0-9]");
  cmsys::RegularExpression vgMPK2(
    "== .*[0-9][0-9]* bytes in [0-9][0-9]* blocks are still reachable"
    " in loss record [0-9][0-9]* of [0-9]");
  cmsys::RegularExpression vgUMC(
    "== .*Conditional jump or move depends on uninitialised value\\(s\\)");
  cmsys::RegularExpression vgUMR1("== .*Use of uninitialised value of size [0-9][0-9]*");
  cmsys::RegularExpression vgUMR2("== .*Invalid read of size [0-9][0-9]*");
  cmsys::RegularExpression vgUMR3("== .*Jump to the invalid address ");
  cmsys::RegularExpression vgUMR4(
    "== .*Syscall param .* contains uninitialised or unaddressable byte\\(s\\)");
  cmsys::RegularExpression vgIPW("== .*Invalid write of size [0-9]");
  cmsys::RegularExpression vgABR("== .*pthread_mutex_unlock: mutex is locked by a different thread");

  //double sttime = cmSystemTools::GetTime();
  //std::cout << "Start test: " << lines.size() << std::endl;
  for ( cc = 0; cc < lines.size(); cc ++ )
    {
    if ( valgrindLine.find(lines[cc]) )
      {
      int failure = cmCTest::NO_MEMORY_FAULT;
      if ( vgFIM.find(lines[cc]) ) { failure = cmCTest::FIM; }
      else if ( vgFMM.find(lines[cc]) ) { failure = cmCTest::FMM; }
      else if ( vgMLK.find(lines[cc]) ) { failure = cmCTest::MLK; }
      else if ( vgPAR.find(lines[cc]) ) { failure = cmCTest::PAR; }
      else if ( vgMPK1.find(lines[cc]) ){ failure = cmCTest::MPK; }
      else if ( vgMPK2.find(lines[cc]) ){ failure = cmCTest::MPK; }
      else if ( vgUMC.find(lines[cc]) ) { failure = cmCTest::UMC; }
      else if ( vgUMR1.find(lines[cc]) ){ failure = cmCTest::UMR; }
      else if ( vgUMR2.find(lines[cc]) ){ failure = cmCTest::UMR; }
      else if ( vgUMR3.find(lines[cc]) ){ failure = cmCTest::UMR; }
      else if ( vgUMR4.find(lines[cc]) ){ failure = cmCTest::UMR; }
      else if ( vgIPW.find(lines[cc]) ) { failure = cmCTest::IPW; }
      else if ( vgABR.find(lines[cc]) ) { failure = cmCTest::ABR; }

      if ( failure != cmCTest::NO_MEMORY_FAULT )
        {
        ostr << "<b>" << cmCTestMemCheckResultStrings[failure] << "</b> ";
        results[failure] ++;
        defects ++;
        }
      ostr << cmCTest::MakeXMLSafe(lines[cc]) << std::endl;
      }
    }
  //std::cout << "End test (elapsed: " << (cmSystemTools::GetTime() - sttime) << std::endl;
  log = ostr.str();
  if ( defects )
    {
    return false;
    }
  return true;
}

bool cmCTest::ProcessMemCheckOutput(const std::string& str, std::string& log, int* results)
{
  std::string::size_type cc;
  for ( cc = 0; cc < cmCTest::NO_MEMORY_FAULT; cc ++ )
    {
    results[cc] = 0;
    }

  if ( m_MemoryTesterStyle == cmCTest::VALGRIND )
    {
    return this->ProcessMemCheckValgrindOutput(str, log, results);
    }
  else if ( m_MemoryTesterStyle == cmCTest::PURIFY )
    {
    return this->ProcessMemCheckPurifyOutput(str, log, results);
    }
  else if ( m_MemoryTesterStyle == cmCTest::BOUNDS_CHECKER )
    {
    log.append("\nMemory checking style used was: ");
    log.append("Bounds Checker");
    }
  else
    {
    log.append("\nMemory checking style used was: ");
    log.append("None that I know");
    log = str;
    }


  return true;
}

int cmCTest::GenerateDartNotesOutput(std::ostream& os, const cmCTest::tm_VectorOfStrings& files)
{
  cmCTest::tm_VectorOfStrings::const_iterator it;
  for ( it = files.begin(); it != files.end(); it ++ )
    {
    if ( !cmSystemTools::FileExists(it->c_str()) )
      {
      std::cerr << "Error creating notes. File " << it->c_str() << " does not exists" << std::endl;
      return 0;
      }
    }

  os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    << "<?xml-stylesheet type=\"text/xsl\" href=\"Dart/Source/Server/XSL/Build.xsl <file:///Dart/Source/Server/XSL/Build.xsl> \"?>\n"
    << "<Site BuildName=\"" << m_DartConfiguration["BuildName"] << "\" BuildStamp=\"" 
    << m_CurrentTag << "-" << this->GetTestModelString() << "\" Name=\"" 
    << m_DartConfiguration["Site"] << "\" Generator=\"ctest-" << CMake_VERSION_FULL
    << "\">\n"
    << "<Notes>" << std::endl;

  for ( it = files.begin(); it != files.end(); it ++ )
    {
    std::cout << "\tAdd file: " << it->c_str() << std::endl;
    std::string note_time = this->CurrentTime();
    os << "<Note Name=\"" << this->MakeXMLSafe(it->c_str()) << "\">\n"
      << "<DateTime>" << note_time << "</DateTime>\n"
      << "<Text>" << std::endl;
    std::ifstream ifs(it->c_str());
    if ( ifs )
      {
      std::string line;
      while ( cmSystemTools::GetLineFromStream(ifs, line) )
        {
        os << this->MakeXMLSafe(line) << std::endl;
        }
      ifs.close();
      }
    else
      {
      os << "Problem reading file: " << it->c_str() << std::endl;
      std::cerr << "Problem reading file: " << it->c_str() << " while creating notes" << std::endl;
      }
    os << "</Text>\n"
      << "</Note>" << std::endl;
    }
  os << "</Notes>\n"
    << "</Site>" << std::endl;
  return 1;
}

int cmCTest::GenerateNotesFile(const char* cfiles)
{
  if ( !cfiles )
    {
    return 1;
    }

  std::vector<cmStdString> files;

  std::cout << "Create notes file" << std::endl;

  files = cmSystemTools::SplitString(cfiles, ';');
  if ( files.size() == 0 )
    {
    return 1;
    }

  std::ofstream ofs;
  if ( !this->OpenOutputFile(m_CurrentTag, "Notes.xml", ofs) )
    {
    std::cerr << "Cannot open notes file" << std::endl;
    return 1;
    }

  this->GenerateDartNotesOutput(ofs, files);
  return 0;
}

int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
{
  this->FindRunningCMake(args[0].c_str());
  const char* ctestExec = "ctest";
  bool cmakeAndTest = false;
  bool performSomeTest = true;
  for(unsigned int i=1; i < args.size(); ++i)
    {
    std::string arg = args[i];
    if(arg.find("-C",0) == 0 && i < args.size() - 1)
      {
      i++;
      this->m_ConfigType = args[i];
      cmSystemTools::ReplaceString(this->m_ConfigType, ".\\", "");
      }

    if( arg.find("-V",0) == 0 || arg.find("--verbose",0) == 0 )
      {
      this->m_Verbose = true;
      this->ScriptHandler->SetVerbose(this->m_Verbose);
      this->UpdateHandler->SetVerbose(this->m_Verbose);
      this->ConfigureHandler->SetVerbose(this->m_Verbose);
      }

    if( arg.find("-N",0) == 0 || arg.find("--show-only",0) == 0 )
      {
      this->m_ShowOnly = true;
      }

    if( arg.find("-S",0) == 0 && i < args.size() - 1 )
      {
      this->m_RunConfigurationScript = true;
      i++;
      this->ScriptHandler->AddConfigurationScript(args[i].c_str());
      }

    if( arg.find("--tomorrow-tag",0) == 0 )
      {
      m_TomorrowTag = true;
      }
    if( arg.find("--force-new-ctest-process",0) == 0 )
      {
      m_ForceNewCTestProcess = true;
      }
    if( arg.find("--interactive-debug-mode",0) == 0 && i < args.size() - 1 )
      {
      i++;
      m_InteractiveDebugMode = cmSystemTools::IsOn(args[i].c_str());
      }
    if( arg.find("--compatibility-mode",0) == 0 )
      {
      m_CompatibilityMode = true;
      }
    if( arg.find("-D",0) == 0 && i < args.size() - 1 )
      {
      this->m_DartMode = true;
      i++;
      std::string targ = args[i];
      if ( targ == "Experimental" )
        {
        this->SetTestModel(cmCTest::EXPERIMENTAL);
        this->SetTest("Start");
        this->SetTest("Configure");
        this->SetTest("Build");
        this->SetTest("Test");
        this->SetTest("Coverage");
        this->SetTest("Submit");
        }
      else if ( targ == "ExperimentalStart" )
        {
        this->SetTestModel(cmCTest::EXPERIMENTAL);
        this->SetTest("Start");
        }
      else if ( targ == "ExperimentalUpdate" )
        {
        this->SetTestModel(cmCTest::EXPERIMENTAL);
        this->SetTest("Update");
        }
      else if ( targ == "ExperimentalConfigure" )
        {
        this->SetTestModel(cmCTest::EXPERIMENTAL);
        this->SetTest("Configure");
        }
      else if ( targ == "ExperimentalBuild" )
        {
        this->SetTestModel(cmCTest::EXPERIMENTAL);
        this->SetTest("Build");
        }
      else if ( targ == "ExperimentalTest" )
        {
        this->SetTestModel(cmCTest::EXPERIMENTAL);
        this->SetTest("Test");
        }
      else if ( targ == "ExperimentalMemCheck"
        || targ == "ExperimentalPurify" )
        {
        this->SetTestModel(cmCTest::EXPERIMENTAL);
        this->SetTest("MemCheck");
        }
      else if ( targ == "ExperimentalCoverage" )
        {
        this->SetTestModel(cmCTest::EXPERIMENTAL);
        this->SetTest("Coverage");
        }
      else if ( targ == "ExperimentalSubmit" )
        {
        this->SetTestModel(cmCTest::EXPERIMENTAL);
        this->SetTest("Submit");
        }
      else if ( targ == "Continuous" )
        {
        this->SetTestModel(cmCTest::CONTINUOUS);
        this->SetTest("Start");
        this->SetTest("Update");
        this->SetTest("Configure");
        this->SetTest("Build");
        this->SetTest("Test");
        this->SetTest("Coverage");
        this->SetTest("Submit");
        }
      else if ( targ == "ContinuousStart" )
        {
        this->SetTestModel(cmCTest::CONTINUOUS);
        this->SetTest("Start");
        }
      else if ( targ == "ContinuousUpdate" )
        {
        this->SetTestModel(cmCTest::CONTINUOUS);
        this->SetTest("Update");
        }  
      else if ( targ == "ContinuousConfigure" )
        {
        this->SetTestModel(cmCTest::CONTINUOUS);
        this->SetTest("Configure");
        }
      else if ( targ == "ContinuousBuild" )
        {
        this->SetTestModel(cmCTest::CONTINUOUS);
        this->SetTest("Build");
        }
      else if ( targ == "ContinuousTest" )
        {
        this->SetTestModel(cmCTest::CONTINUOUS);
        this->SetTest("Test");
        }
      else if ( targ == "ContinuousMemCheck"
        || targ == "ContinuousPurify" )
        {
        this->SetTestModel(cmCTest::CONTINUOUS);
        this->SetTest("MemCheck");
        }
      else if ( targ == "ContinuousCoverage" )
        {
        this->SetTestModel(cmCTest::CONTINUOUS);
        this->SetTest("Coverage");
        }
      else if ( targ == "ContinuousSubmit" )
        {
        this->SetTestModel(cmCTest::CONTINUOUS);
        this->SetTest("Submit");
        }
      else if ( targ == "Nightly" )
        {
        this->SetTestModel(cmCTest::NIGHTLY);
        this->SetTest("Start");
        this->SetTest("Update");
        this->SetTest("Configure");
        this->SetTest("Build");
        this->SetTest("Test");
        this->SetTest("Coverage");
        this->SetTest("Submit");
        }
      else if ( targ == "NightlyStart" )
        {
        this->SetTestModel(cmCTest::NIGHTLY);
        this->SetTest("Start");
        }
      else if ( targ == "NightlyUpdate" )
        {
        this->SetTestModel(cmCTest::NIGHTLY);
        this->SetTest("Update");
        }
      else if ( targ == "NightlyConfigure" )
        {
        this->SetTestModel(cmCTest::NIGHTLY);
        this->SetTest("Configure");
        }
      else if ( targ == "NightlyBuild" )
        {
        this->SetTestModel(cmCTest::NIGHTLY);
        this->SetTest("Build");
        }
      else if ( targ == "NightlyTest" )
        {
        this->SetTestModel(cmCTest::NIGHTLY);
        this->SetTest("Test");
        }
      else if ( targ == "NightlyMemCheck"
        || targ == "NightlyPurify" )
        {
        this->SetTestModel(cmCTest::NIGHTLY);
        this->SetTest("MemCheck");
        }
      else if ( targ == "NightlyCoverage" )
        {
        this->SetTestModel(cmCTest::NIGHTLY);
        this->SetTest("Coverage");
        }
      else if ( targ == "NightlySubmit" )
        {
        this->SetTestModel(cmCTest::NIGHTLY);
        this->SetTest("Submit");
        }
      else if ( targ == "MemoryCheck" )
        {
        this->SetTestModel(cmCTest::EXPERIMENTAL);
        this->SetTest("Start");
        this->SetTest("Configure");
        this->SetTest("Build");
        this->SetTest("MemCheck");
        this->SetTest("Coverage");
        this->SetTest("Submit");
        }
      else if ( targ == "NightlyMemoryCheck" )
        {
        this->SetTestModel(cmCTest::NIGHTLY);
        this->SetTest("Start");
        this->SetTest("Update");
        this->SetTest("Configure");
        this->SetTest("Build");
        this->SetTest("MemCheck");
        this->SetTest("Coverage");
        this->SetTest("Submit");
        }
      else
        {
        performSomeTest = false;
        std::cerr << "CTest -D called with incorrect option: " << targ << std::endl;
        std::cerr << "Available options are:" << std::endl
          << "  " << ctestExec << " -D Continuous" << std::endl
          << "  " << ctestExec << " -D Continuous(Start|Update|Configure|Build)" << std::endl
          << "  " << ctestExec << " -D Continuous(Test|Coverage|MemCheck|Submit)" << std::endl
          << "  " << ctestExec << " -D Experimental" << std::endl
          << "  " << ctestExec << " -D Experimental(Start|Update|Configure|Build)" << std::endl
          << "  " << ctestExec << " -D Experimental(Test|Coverage|MemCheck|Submit)" << std::endl
          << "  " << ctestExec << " -D Nightly" << std::endl
          << "  " << ctestExec << " -D Nightly(Start|Update|Configure|Build)" << std::endl
          << "  " << ctestExec << " -D Nightly(Test|Coverage|MemCheck|Submit)" << std::endl
          << "  " << ctestExec << " -D NightlyMemoryCheck" << std::endl;
          ;
        }
      }

    if( ( arg.find("-T",0) == 0 ) && 
      (i < args.size() -1) )
      {
      this->m_DartMode = true;
      i++;
      if ( !this->SetTest(args[i].c_str(), false) )
        {
        performSomeTest = false;
        std::cerr << "CTest -T called with incorrect option: " << args[i].c_str() << std::endl;
        std::cerr << "Available options are:" << std::endl
          << "  " << ctestExec << " -T all" << std::endl
          << "  " << ctestExec << " -T start" << std::endl
          << "  " << ctestExec << " -T update" << std::endl
          << "  " << ctestExec << " -T configure" << std::endl
          << "  " << ctestExec << " -T build" << std::endl
          << "  " << ctestExec << " -T test" << std::endl
          << "  " << ctestExec << " -T coverage" << std::endl
          << "  " << ctestExec << " -T memcheck" << std::endl
          << "  " << ctestExec << " -T notes" << std::endl
          << "  " << ctestExec << " -T submit" << std::endl;
        }
      }

    if( ( arg.find("-M",0) == 0 || arg.find("--test-model",0) == 0 ) &&
      (i < args.size() -1) )
      {
      i++;
      std::string const& str = args[i];
      if ( cmSystemTools::LowerCase(str) == "nightly" )
        {
        this->SetTestModel(cmCTest::NIGHTLY);
        }
      else if ( cmSystemTools::LowerCase(str) == "continuous" )
        {
        this->SetTestModel(cmCTest::CONTINUOUS);
        }
      else if ( cmSystemTools::LowerCase(str) == "experimental" )
        {
        this->SetTestModel(cmCTest::EXPERIMENTAL);
        }
      else
        {
        performSomeTest = false;
        std::cerr << "CTest -M called with incorrect option: " << str.c_str() << std::endl;
        std::cerr << "Available options are:" << std::endl
          << "  " << ctestExec << " -M Continuous" << std::endl
          << "  " << ctestExec << " -M Experimental" << std::endl
          << "  " << ctestExec << " -M Nightly" << std::endl;
        }
      }

    if(arg.find("-I",0) == 0 && i < args.size() - 1)
      {
      i++;
      this->SetTestsToRunInformation(args[i].c_str());
      }
    if(arg.find("-R",0) == 0 && i < args.size() - 1)
      {
      this->m_UseIncludeRegExp = true;
      i++;
      this->m_IncludeRegExp  = args[i];
      }

    if(arg.find("-E",0) == 0 && i < args.size() - 1)
      {
      this->m_UseExcludeRegExp = true;
      i++;
      this->m_ExcludeRegExp  = args[i];
      this->m_UseExcludeRegExpFirst = this->m_UseIncludeRegExp ? false : true;
      }

    if(arg.find("-A",0) == 0 && i < args.size() - 1)
      {
      this->m_DartMode = true;
      this->SetTest("Notes");
      i++;
      this->SetNotesFiles(args[i].c_str());
      }

    // --build-and-test options
    if(arg.find("--build-and-test",0) == 0 && i < args.size() - 1)
      {
      cmakeAndTest = true;
      if(i+2 < args.size())
        {
        i++;
        m_SourceDir = args[i];
        i++;
        m_BinaryDir = args[i];
        // dir must exist before CollapseFullPath is called
        cmSystemTools::MakeDirectory(m_BinaryDir.c_str());
        m_BinaryDir = cmSystemTools::CollapseFullPath(m_BinaryDir.c_str());
        m_SourceDir = cmSystemTools::CollapseFullPath(m_SourceDir.c_str());
        }
      else
        {
        std::cerr << "--build-and-test must have source and binary dir\n";
        }
      }
    if(arg.find("--build-target",0) == 0 && i < args.size() - 1)
      {
      i++;
      m_BuildTarget = args[i];
      }
    if(arg.find("--build-nocmake",0) == 0)
      {
      m_BuildNoCMake = true;
      }
    if(arg.find("--build-run-dir",0) == 0 && i < args.size() - 1)
      {
      i++;
      m_BuildRunDir = args[i];
      }
    if(arg.find("--build-two-config",0) == 0)
      {
      m_BuildTwoConfig = true;
      }
    if(arg.find("--build-exe-dir",0) == 0 && i < args.size() - 1)
      {
      i++;
      m_ExecutableDirectory = args[i];
      }
    if(arg.find("--build-generator",0) == 0 && i < args.size() - 1)
      {
      i++;
      m_BuildGenerator = args[i];
      }
    if(arg.find("--build-project",0) == 0 && i < args.size() - 1)
      {
      i++;
      m_BuildProject = args[i];
      }
    if(arg.find("--build-makeprogram",0) == 0 && i < args.size() - 1)
      {
      i++;
      m_BuildMakeProgram = args[i];
      }
    if(arg.find("--build-noclean",0) == 0)
      {
      m_BuildNoClean = true;
      }
    if(arg.find("--build-options",0) == 0 && i < args.size() - 1)
      {
      ++i;
      bool done = false;
      while(i < args.size() && !done)
        {
        m_BuildOptions.push_back(args[i]);
        if(i+1 < args.size() 
          && (args[i+1] == "--build-target" || args[i+1] == "--test-command"))
          {
          done = true;
          }
        else
          {
          ++i;
          }
        }
      }
    if(arg.find("--test-command",0) == 0 && i < args.size() - 1)
      {
      ++i;
      m_TestCommand = args[i];
      while(i+1 < args.size())
        {
        ++i;
        m_TestCommandArgs.push_back(args[i]);
        }
      }
    }

  if(cmakeAndTest)
    {
    cmSystemTools::ResetErrorOccuredFlag();
    cmListFileCache::GetInstance()->ClearCache();
    int retv = this->RunCMakeAndTest(output);
    cmSystemTools::ResetErrorOccuredFlag();
    cmListFileCache::GetInstance()->ClearCache();
#ifdef CMAKE_BUILD_WITH_CMAKE
    cmDynamicLoader::FlushCache();
#endif
    return retv;
    }

  if(performSomeTest )
    {
    int res;
    // call process directory
    if (this->m_RunConfigurationScript)
      {
      res = this->ScriptHandler->RunConfigurationScript();
      }
    else
      {
      if ( !this->Initialize() )
        {
        res = 12;
        }
      else
        {
        res = this->ProcessTests();
        }
      this->Finalize();
      }
    return res;
    }
  return 1;
}

void cmCTest::FindRunningCMake(const char* arg0)
{
  // Find our own executable.
  std::vector<cmStdString> failures;
  m_CTestSelf = arg0;
  cmSystemTools::ConvertToUnixSlashes(m_CTestSelf);
  failures.push_back(m_CTestSelf);
  m_CTestSelf = cmSystemTools::FindProgram(m_CTestSelf.c_str());
  if(!cmSystemTools::FileExists(m_CTestSelf.c_str()))
    {
    failures.push_back(m_CTestSelf);
    m_CTestSelf =  "/usr/local/bin/ctest";
    }
  if(!cmSystemTools::FileExists(m_CTestSelf.c_str()))
    {
    failures.push_back(m_CTestSelf);
    cmOStringStream msg;
    msg << "CTEST can not find the command line program cmake.\n";
    msg << "  argv[0] = \"" << arg0 << "\"\n";
    msg << "  Attempted paths:\n";
    std::vector<cmStdString>::iterator i;
    for(i=failures.begin(); i != failures.end(); ++i)
      {
      msg << "    \"" << i->c_str() << "\"\n";
      }
    cmSystemTools::Error(msg.str().c_str());
    }
  std::string dir;
  std::string file;
  if(cmSystemTools::SplitProgramPath(m_CTestSelf.c_str(),
      dir,
      file,
      true))
    {
    m_CMakeSelf = dir += "/cmake";
    m_CMakeSelf += cmSystemTools::GetExecutableExtension();
    if(!cmSystemTools::FileExists(m_CMakeSelf.c_str()))
      {
      cmOStringStream msg;
      failures.push_back(m_CMakeSelf);
      msg << "CTEST can not find the command line program cmake.\n";
      msg << "  argv[0] = \"" << arg0 << "\"\n";
      msg << "  Attempted path:\n";
      msg << "    \"" << m_CMakeSelf.c_str() << "\"\n"; 
      cmSystemTools::Error(msg.str().c_str());
      }
    }
}

void CMakeMessageCallback(const char* m, const char*, bool&, void* s)
{
  std::string* out = (std::string*)s;
  *out += m;
  *out += "\n";
}

void CMakeStdoutCallback(const char* m, int len, void* s)
{
  std::string* out = (std::string*)s;
  out->append(m, len);
}


int cmCTest::RunCMakeAndTest(std::string* outstring)
{  
  unsigned int k;
  std::string cmakeOutString;
  cmSystemTools::SetErrorCallback(CMakeMessageCallback, &cmakeOutString);
  cmSystemTools::SetStdoutCallback(CMakeStdoutCallback, &cmakeOutString);
  cmOStringStream out;
  cmake cm;
  double timeout = m_TimeOut;
  // default to the build type of ctest itself
  if(m_ConfigType.size() == 0)
    {
#ifdef  CMAKE_INTDIR
    m_ConfigType = CMAKE_INTDIR;
#endif
    }

  std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
  out << "Internal cmake changing into directory: " << m_BinaryDir << "\n";  
  if (!cmSystemTools::FileIsDirectory(m_BinaryDir.c_str()))
    {
    cmSystemTools::MakeDirectory(m_BinaryDir.c_str());
    }
  cmSystemTools::ChangeDirectory(m_BinaryDir.c_str());
  if(!m_BuildNoCMake)
    {
    std::vector<std::string> args;
    args.push_back(m_CMakeSelf);
    args.push_back(m_SourceDir);
    if(m_BuildGenerator.size())
      {
      std::string generator = "-G";
      generator += m_BuildGenerator;
      args.push_back(generator);
      }
    if ( m_ConfigType.size() > 0 )
      {
      std::string btype = "-DBUILD_TYPE:STRING=" + m_ConfigType;
      args.push_back(btype);
      }

    for(k=0; k < m_BuildOptions.size(); ++k)
      {
      args.push_back(m_BuildOptions[k]);
      }
    if (cm.Run(args) != 0)
      {
      out << "Error: cmake execution failed\n";
      out << cmakeOutString << "\n";
      // return to the original directory
      cmSystemTools::ChangeDirectory(cwd.c_str());
      if(outstring)
        {
        *outstring = out.str();
        }
      else
        {
        std::cerr << out.str() << "\n";
        }
      return 1;
      }
    if(m_BuildTwoConfig)
      {
      if (cm.Run(args) != 0)
        {
        out << "Error: cmake execution failed\n";
        out << cmakeOutString << "\n";
        // return to the original directory
        cmSystemTools::ChangeDirectory(cwd.c_str());
        if(outstring)
          {
          *outstring = out.str();
          }
        else
          {
          std::cerr << out.str() << "\n";
          }
        return 1;
        }
      } 
    }

  cmSystemTools::SetErrorCallback(0, 0);
  out << cmakeOutString << "\n";
  if(m_BuildMakeProgram.size() == 0)
    {
    out << "Error: cmake does not have a valid MAKEPROGRAM\n";
    out << "Did you specify a --build-makeprogram and a --build-generator?\n";
    if(outstring)
      {
      *outstring = out.str();
      }
    else
      {
      std::cerr << out.str() << "\n";
      }
    return 1;
    }
  int retVal = 0;
  std::string makeCommand = cmSystemTools::ConvertToOutputPath(m_BuildMakeProgram.c_str());
  std::string lowerCaseCommand = cmSystemTools::LowerCase(makeCommand);
  // if msdev is the make program then do the following
  // MSDEV 6.0
  if(lowerCaseCommand.find("msdev") != std::string::npos)
    {
    // if there are spaces in the makeCommand, assume a full path
    // and convert it to a path with no spaces in it as the
    // RunSingleCommand does not like spaces
#if defined(_WIN32) && !defined(__CYGWIN__)      
    if(makeCommand.find(' ') != std::string::npos)
      {
      cmSystemTools::GetShortPath(makeCommand.c_str(), makeCommand);
      }
#endif
    makeCommand += " ";
    makeCommand += m_BuildProject;
    makeCommand += ".dsw /MAKE \"ALL_BUILD - ";
    makeCommand += m_ConfigType;
    if(m_BuildNoClean)
      {
      makeCommand += "\" /BUILD";
      }
    else
      {
      makeCommand += "\" /REBUILD";
      }
    }
  // MSDEV 7.0 .NET
  else if (lowerCaseCommand.find("devenv") != std::string::npos)
    {
#if defined(_WIN32) && !defined(__CYGWIN__)      
    if(makeCommand.find(' ') != std::string::npos)
      {
      cmSystemTools::GetShortPath(makeCommand.c_str(), makeCommand);
      }
#endif
    makeCommand += " ";
    makeCommand += m_BuildProject;
    makeCommand += ".sln ";
    if(m_BuildNoClean)
      {
      makeCommand += "/build ";
      }
    else
      {
      makeCommand += "/rebuild ";
      }
    makeCommand += m_ConfigType + " /project ALL_BUILD";
    }
  else if (lowerCaseCommand.find("make") != std::string::npos)
    {
    // assume a make sytle program
    // clean first
    if(!m_BuildNoClean)
      {
      std::string cleanCommand = makeCommand;
      cleanCommand += " clean";
      out << "Running make clean command: " << cleanCommand.c_str() << " ...\n";
      retVal = 0;
      std::string output;
      if (!cmSystemTools::RunSingleCommand(cleanCommand.c_str(), &output, &retVal, 0,
                                           false, timeout) ||
        retVal)
        {
        out << "Error: " << cleanCommand.c_str() << "  execution failed\n";
        out << output.c_str() << "\n";
        // return to the original directory
        cmSystemTools::ChangeDirectory(cwd.c_str());
        out << "Return value: " << retVal << std::endl;
        if(outstring)
          {
          *outstring = out.str();
          }
        else
          {
          std::cerr << out.str() << "\n";
          }
        return 1;
        }
      out << output;
      }

    if(m_BuildTarget.size())
      {
      makeCommand +=  " ";
      makeCommand += m_BuildTarget;
      }
    }

  // command line make program

  out << "Running make command: " << makeCommand.c_str() << "\n";
  retVal = 0;
  std::string output;
  if (!cmSystemTools::RunSingleCommand(makeCommand.c_str(), &output, &retVal, 0, false, timeout))
    {
    out << "Error: " << makeCommand.c_str() <<  "  execution failed\n";
    out << output.c_str() << "\n";
    // return to the original directory
    cmSystemTools::ChangeDirectory(cwd.c_str());
    out << "Return value: " << retVal << std::endl;
    if(outstring)
      {
      *outstring = out.str();
      }
    else
      {
      std::cerr << out.str() << "\n";
      }
    return 1;
    }
  if ( retVal )
    {
    if(outstring)
      {
      *outstring = out.str();
      *outstring += "Building of project failed\n";
      *outstring += output;
      *outstring += "\n";
      }
    else
      {
      std::cerr << "Building of project failed\n";
      std::cerr << out.str() << output << "\n";
      }
    // return to the original directory
    cmSystemTools::ChangeDirectory(cwd.c_str());
    return 1;
    }
  out << output;

  if(m_TestCommand.size() == 0)
    {
    if(outstring)
      {
      *outstring = out.str();
      }
    else
      {
      std::cout << out.str() << "\n";
      }
    return retVal;
    }

  // now run the compiled test if we can find it
  std::vector<std::string> attempted;
  std::vector<std::string> failed;
  std::string tempPath;
  std::string filepath = 
    cmSystemTools::GetFilenamePath(m_TestCommand);
  std::string filename = 
    cmSystemTools::GetFilenameName(m_TestCommand);
  // if full path specified then search that first
  if (filepath.size())
    {
    tempPath = filepath;
    tempPath += "/";
    tempPath += filename;
    attempted.push_back(tempPath);
    if(m_ConfigType.size())
      {
      tempPath = filepath;
      tempPath += "/";
      tempPath += m_ConfigType;
      tempPath += "/";
      tempPath += filename;
      attempted.push_back(tempPath);
      }
    }
  // otherwise search local dirs
  else
    {
    attempted.push_back(filename);
    if(m_ConfigType.size())
      {
      tempPath = m_ConfigType;
      tempPath += "/";
      tempPath += filename;
      attempted.push_back(tempPath);
      }
    }
  // if m_ExecutableDirectory is set try that as well
  if (m_ExecutableDirectory.size())
    {
    tempPath = m_ExecutableDirectory;
    tempPath += "/";
    tempPath += m_TestCommand;
    attempted.push_back(tempPath);
    if(m_ConfigType.size())
      {
      tempPath = m_ExecutableDirectory;
      tempPath += "/";
      tempPath += m_ConfigType;
      tempPath += "/";
      tempPath += filename;
      attempted.push_back(tempPath);
      }
    }

  // store the final location in fullPath
  std::string fullPath;
  
  // now look in the paths we specified above
  for(unsigned int ai=0; 
      ai < attempted.size() && fullPath.size() == 0; ++ai)
    {
    // first check without exe extension
    if(cmSystemTools::FileExists(attempted[ai].c_str())
       && !cmSystemTools::FileIsDirectory(attempted[ai].c_str()))
      {
      fullPath = cmSystemTools::CollapseFullPath(attempted[ai].c_str());
      }
    // then try with the exe extension
    else
      {
      failed.push_back(attempted[ai].c_str());
      tempPath = attempted[ai];
      tempPath += cmSystemTools::GetExecutableExtension();
      if(cmSystemTools::FileExists(tempPath.c_str())
         && !cmSystemTools::FileIsDirectory(tempPath.c_str()))
        {
        fullPath = cmSystemTools::CollapseFullPath(tempPath.c_str());
        }
      else
        {
        failed.push_back(tempPath.c_str());
        }
      }
    }

  if(!cmSystemTools::FileExists(fullPath.c_str()))
    {
    out << "Could not find path to executable, perhaps it was not built: " <<
      m_TestCommand << "\n";
    out << "tried to find it in these places:\n";
    out << fullPath.c_str() << "\n";
    for(unsigned int i=0; i < failed.size(); ++i)
      {
      out << failed[i] << "\n";
      }
    if(outstring)
      {
      *outstring =  out.str();
      }
    else
      {
      std::cerr << out.str();
      }
    // return to the original directory
    cmSystemTools::ChangeDirectory(cwd.c_str());
    return 1;
    }

  std::vector<const char*> testCommand;
  testCommand.push_back(fullPath.c_str());
  for(k=0; k < m_TestCommandArgs.size(); ++k)
    {
    testCommand.push_back(m_TestCommandArgs[k].c_str());
    }
  testCommand.push_back(0);
  std::string outs;
  int retval = 0;
  // run the test from the m_BuildRunDir if set
  if(m_BuildRunDir.size())
    {
    out << "Run test in directory: " << m_BuildRunDir << "\n";
    cmSystemTools::ChangeDirectory(m_BuildRunDir.c_str());
    }
  out << "Running test executable: " << fullPath << " ";
  for(k=0; k < m_TestCommandArgs.size(); ++k)
    {
    out << m_TestCommandArgs[k] << " ";
    }
  out << "\n";
  m_TimeOut = timeout;
  int runTestRes = this->RunTest(testCommand, &outs, &retval, 0);
  if(runTestRes != cmsysProcess_State_Exited || retval != 0)
    {
    out << "Failed to run test command: " << testCommand[0] << "\n";
    retval = 1;
    }

  out << outs << "\n";
  if(outstring)
    {
    *outstring = out.str();
    }
  else
    {
    std::cout << out.str() << "\n";
    }
  return retval;
}

void cmCTest::SetNotesFiles(const char* notes)
{
  if ( !notes )
    {
    return;
    }
  m_NotesFiles = notes;
}

int cmCTest::ReadCustomConfigurationFileTree(const char* dir)
{
  tm_VectorOfStrings dirs;
  tm_VectorOfStrings ndirs;
  dirs.push_back(dir);
  cmake cm;
  cmGlobalGenerator gg;
  gg.SetCMakeInstance(&cm);
  std::auto_ptr<cmLocalGenerator> lg(gg.CreateLocalGenerator());
  lg->SetGlobalGenerator(&gg);
  cmMakefile *mf = lg->GetMakefile();

  while ( dirs.size() > 0 )
    {
    tm_VectorOfStrings::iterator cdir = dirs.end()-1;
    std::string rexpr = *cdir + "/*";
    std::string fname = *cdir + "/CTestCustom.ctest";
    if ( cmSystemTools::FileExists(fname.c_str()) && 
      (!lg->GetMakefile()->ReadListFile(0, fname.c_str()) ||
       cmSystemTools::GetErrorOccuredFlag() ) )
      {
      std::cerr << "Problem reading custom configuration" << std::endl;
      }
    dirs.erase(dirs.end()-1, dirs.end());
    cmSystemTools::SimpleGlob(rexpr, ndirs, -1);
    dirs.insert(dirs.end(), ndirs.begin(), ndirs.end());
    }

  this->PopulateCustomVector(mf, "CTEST_CUSTOM_ERROR_MATCH", m_CustomErrorMatches);
  this->PopulateCustomVector(mf, "CTEST_CUSTOM_ERROR_EXCEPTION", m_CustomErrorExceptions);
  this->PopulateCustomVector(mf, "CTEST_CUSTOM_WARNING_MATCH", m_CustomWarningMatches);
  this->PopulateCustomVector(mf, "CTEST_CUSTOM_WARNING_EXCEPTION", m_CustomWarningExceptions);

  this->PopulateCustomVector(mf, "CTEST_CUSTOM_TESTS_IGNORE", m_CustomTestsIgnore);
  this->PopulateCustomVector(mf, "CTEST_CUSTOM_MEMCHECK_IGNORE", m_CustomMemCheckIgnore);

  this->PopulateCustomVector(mf, "CTEST_CUSTOM_PRE_TEST", m_CustomPreTest);
  this->PopulateCustomVector(mf, "CTEST_CUSTOM_POST_TEST", m_CustomPostTest);
  this->PopulateCustomVector(mf, "CTEST_CUSTOM_PRE_MEMCHECK", m_CustomPreMemCheck);
  this->PopulateCustomVector(mf, "CTEST_CUSTOM_POST_MEMCHECK", m_CustomPostMemCheck);

  const char* maxstr = mf->GetDefinition("CTEST_CUSTOM_PASSED_TEST_STRING_MAXLEN");
  if ( maxstr )
    {
    long val = atoi(maxstr);
    if ( val > 0 )
      {
      m_MaximumPassedTestResultSize = val;
      }
    }
  maxstr = mf->GetDefinition("CTEST_CUSTOM_FAILED_TEST_STRING_MAXLEN");
  if ( maxstr )
    {
    long val = atoi(maxstr);
    if ( val > 0 )
      {
      m_MaximumFailedTestResultSize = val;
      }
    }

  return 1;
}

void cmCTest::PopulateCustomVector(cmMakefile* mf, const char* def, tm_VectorOfStrings& vec)
{
  if ( !def)
    {
    return;
    }
  const char* dval = mf->GetDefinition(def);
  if ( !dval )
    {
    return;
    }
  std::vector<std::string> slist;
  cmSystemTools::ExpandListArgument(dval, slist);
  std::vector<std::string>::iterator it;

  for ( it = slist.begin(); it != slist.end(); ++it )
    {
    vec.push_back(it->c_str());
    }
}

int cmCTest::ExecuteCommands(tm_VectorOfStrings& vec)
{
  tm_VectorOfStrings::iterator it;
  for ( it = vec.begin(); it != vec.end(); ++it )
    {
    int retVal = 0;
    if ( m_Verbose )
      {
      std::cout << "Run command: " << *it << std::endl;
      }
    if ( !cmSystemTools::RunSingleCommand(it->c_str(), 0, &retVal, 0, true /*m_Verbose*/) || 
      retVal != 0 )
      {
      std::cerr << "Problem running command: " << *it << std::endl;
      return 0;
      }
    }
  return 1;
}


// get the next number in a string with numbers separated by ,
// pos is the start of the search and pos2 is the end of the search
// pos becomes pos2 after a call to GetNextNumber.   
// -1 is returned at the end of the list.
inline int GetNextNumber(std::string const& in, 
                         int& val,
                         std::string::size_type& pos,
                         std::string::size_type& pos2)
{
  pos2 = in.find(',', pos);
  if(pos2 != in.npos)
    {
    if(pos2-pos == 0)
      {
      val = -1;
      }
    else
      {
      val = atoi(in.substr(pos, pos2-pos).c_str());
      }
    pos = pos2+1;
    return 1;
    }
  else
    {
    if(in.size()-pos == 0)
      {
       val = -1;
      }
    else
      {
      val = atoi(in.substr(pos, in.size()-pos).c_str());
      }
    return 0;
    }
}

// get the next number in a string with numbers separated by ,
// pos is the start of the search and pos2 is the end of the search
// pos becomes pos2 after a call to GetNextNumber.   
// -1 is returned at the end of the list.
inline int GetNextRealNumber(std::string const& in, 
                             double& val,
                             std::string::size_type& pos,
                             std::string::size_type& pos2)
{
  pos2 = in.find(',', pos);
  if(pos2 != in.npos)
    {
    if(pos2-pos == 0)
      {
      val = -1;
      }
    else
      {
      val = atof(in.substr(pos, pos2-pos).c_str());
      }
    pos = pos2+1;
    return 1;
    }
  else
    {
    if(in.size()-pos == 0)
      {
       val = -1;
      }
    else
      {
      val = atof(in.substr(pos, in.size()-pos).c_str());
      }
    return 0;
    }
}

                         
void cmCTest::SetTestsToRunInformation(const char* in)
{
  this->TestsToRunString = in;
  // if the argument is a file, then read it and use the contents as the string
  if(cmSystemTools::FileExists(in))
    {
    std::ifstream fin(in);
    unsigned long filelen = cmSystemTools::FileLength(in);
    char* buff = new char[filelen+1];
    fin.getline(buff, filelen);
    buff[fin.gcount()] = 0;
    this->TestsToRunString = buff;
    }
}

void cmCTest::ExpandTestsToRunInformation(int numTests)
{
  if (this->TestsToRunString.empty())
    {
    return;
    }
  
  int start;
  int end = -1;
  double stride = -1;
  std::string::size_type pos = 0;
  std::string::size_type pos2;
  // read start
  if(GetNextNumber(this->TestsToRunString, start, pos, pos2))
    {
    // read end
    if(GetNextNumber(this->TestsToRunString, end, pos, pos2))
      {
      // read stride
      if(GetNextRealNumber(this->TestsToRunString, stride, pos, pos2))
        {
        int val =0;
        // now read specific numbers
        while(GetNextNumber(this->TestsToRunString, val, pos, pos2))
          {
          m_TestsToRun.push_back(val);
          }
        m_TestsToRun.push_back(val);
        }
      }
    }

  // if start is not specified then we assume we start at 1
  if(start == -1)
    {
    start = 1;
    }

  // if end isnot specified then we assume we end with the last test
  if(end == -1)
    {
    end = numTests;
    }
  
  // if the stride wasn't specified then it defaults to 1
  if(stride == -1)
    {
    stride = 1;
    }

  // if we have a range then add it
  if(end != -1 && start != -1 && stride > 0)
    {
    int i = 0;
    while (i*stride + start <= end)
      {
      m_TestsToRun.push_back(static_cast<int>(i*stride+start));
      ++i;
      }
    }

  // sort the array
  std::sort(m_TestsToRun.begin(), m_TestsToRun.end(), std::less<int>());
  // remove duplicates
  std::vector<int>::iterator new_end = 
    std::unique(m_TestsToRun.begin(), m_TestsToRun.end());
  m_TestsToRun.erase(new_end, m_TestsToRun.end());
  std::cout << "Running tests: ";
  for(unsigned int i =0; i < m_TestsToRun.size(); ++i)
    {
    std::cout << m_TestsToRun[i] << " ";
    }
  std::cout << "\n";
}

std::string cmCTest::GetDartConfiguration(const char *name)
{
  return m_DartConfiguration[name];
}

  
std::string cmCTest::GetCurrentTag()
{
  return m_CurrentTag;
}

bool cmCTest::GetShowOnly()
{
  return m_ShowOnly;
}
