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
#include "cmSystemTools.h"   
#include <ctype.h>
#include <errno.h>
#include <time.h>

#include <cmsys/RegularExpression.hxx>
#include <cmsys/Directory.hxx>
#include <cmsys/Process.h>

// support for realpath call
#ifndef _WIN32
#include <limits.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/wait.h>
#endif

#if defined(_WIN32) && (defined(_MSC_VER) || defined(__BORLANDC__))
#include <string.h>
#include <windows.h>
#include <direct.h>
#include <io.h>
#define _unlink unlink
#else
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#endif

#include <sys/stat.h>

#if defined(CMAKE_BUILD_WITH_CMAKE)
#  include <libtar/libtar.h>
#  include <memory> // auto_ptr
#  include <fcntl.h>
#  include <cmzlib/zlib.h>
#endif

#if defined(__sgi) && !defined(__GNUC__)
# pragma set woff 1375 /* base class destructor not virtual */
#endif

bool cmSystemTools::s_RunCommandHideConsole = false;
bool cmSystemTools::s_DisableRunCommandOutput = false;
bool cmSystemTools::s_ErrorOccured = false;
bool cmSystemTools::s_FatalErrorOccured = false;
bool cmSystemTools::s_DisableMessages = false;
bool cmSystemTools::s_ForceUnixPaths = false;

std::string cmSystemTools::s_Windows9xComspecSubstitute = "command.com";
void cmSystemTools::SetWindows9xComspecSubstitute(const char* str)
{
  if ( str )
    {
    cmSystemTools::s_Windows9xComspecSubstitute = str;
    }
}
const char* cmSystemTools::GetWindows9xComspecSubstitute()
{
  return cmSystemTools::s_Windows9xComspecSubstitute.c_str();
}

void (*cmSystemTools::s_ErrorCallback)(const char*, const char*, bool&, void*);
void (*cmSystemTools::s_StdoutCallback)(const char*, int len, void*);
void* cmSystemTools::s_ErrorCallbackClientData = 0;
void* cmSystemTools::s_StdoutCallbackClientData = 0;

// replace replace with with as many times as it shows up in source.
// write the result into source.
#if defined(_WIN32) && !defined(__CYGWIN__)
void cmSystemTools::ExpandRegistryValues(std::string& source)
{
  // Regular expression to match anything inside [...] that begins in HKEY.
  // Note that there is a special rule for regular expressions to match a
  // close square-bracket inside a list delimited by square brackets.
  // The "[^]]" part of this expression will match any character except
  // a close square-bracket.  The ']' character must be the first in the
  // list of characters inside the [^...] block of the expression.
  cmsys::RegularExpression regEntry("\\[(HKEY[^]]*)\\]");
  
  // check for black line or comment
  while (regEntry.find(source))
    {
    // the arguments are the second match
    std::string key = regEntry.match(1);
    std::string val;
    if (ReadRegistryValue(key.c_str(), val))
      {
      std::string reg = "[";
      reg += key + "]";
      cmSystemTools::ReplaceString(source, reg.c_str(), val.c_str());
      }
    else
      {
      std::string reg = "[";
      reg += key + "]";
      cmSystemTools::ReplaceString(source, reg.c_str(), "/registry");
      }
    }
}
#else
void cmSystemTools::ExpandRegistryValues(std::string&)
{
}
#endif

std::string cmSystemTools::EscapeQuotes(const char* str)
{
  std::string result = "";
  for(const char* ch = str; *ch != '\0'; ++ch)
    {
    if(*ch == '"')
      {
      result += '\\';
      }
    result += *ch;
    }
  return result;
}

std::string cmSystemTools::EscapeSpaces(const char* str)
{
#if defined(_WIN32) && !defined(__CYGWIN__)
  bool useDoubleQ = true;
#else
  bool useDoubleQ = false;
#endif
  if(cmSystemTools::s_ForceUnixPaths)
    {
    useDoubleQ = false;
    }
  
  if(useDoubleQ)
    {
    std::string result;
    
    // if there are spaces
    std::string temp = str;
    if (temp.find(" ") != std::string::npos && 
        temp.find("\"")==std::string::npos)
      {
      result = "\"";
      result += str;
      result += "\"";
      return result;
      }
    return str;
    }
  else
    {
    std::string result = "";
    for(const char* ch = str; *ch != '\0'; ++ch)
      {
      if(*ch == ' ')
        {
        result += '\\';
        }
      result += *ch;
      }
    return result;
    }
}


std::string cmSystemTools::RemoveEscapes(const char* s)
{
  std::string result = "";
  for(const char* ch = s; *ch; ++ch)
    {
    if(*ch == '\\' && *(ch+1) != ';')
      {
      ++ch;
      switch (*ch)
        {
        case '\\': result.insert(result.end(), '\\'); break;
        case '"': result.insert(result.end(), '"'); break;
        case ' ': result.insert(result.end(), ' '); break;
        case 't': result.insert(result.end(), '\t'); break;
        case 'n': result.insert(result.end(), '\n'); break;
        case 'r': result.insert(result.end(), '\r'); break;
        case '#': result.insert(result.end(), '#'); break;
        case '(': result.insert(result.end(), '('); break;
        case ')': result.insert(result.end(), ')'); break;
        case '0': result.insert(result.end(), '\0'); break;
        case '\0':
          {
          cmSystemTools::Error("Trailing backslash in argument:\n", s);
          return result;
          }
        default:
          {
          std::string chStr(1, *ch);
          cmSystemTools::Error("Invalid escape sequence \\", chStr.c_str(),
                               "\nin argument ", s);
          }
        }
      }
    else
      {
      result.insert(result.end(), *ch);
      }
    }
  return result;
}

void cmSystemTools::Error(const char* m1, const char* m2,
                          const char* m3, const char* m4)
{
  std::string message = "CMake Error: ";
  if(m1)
    {
    message += m1;
    }
  if(m2)
    {
    message += m2;
    }
  if(m3)
    {
    message += m3;
    }
  if(m4)
    {
    message += m4;
    }
  cmSystemTools::s_ErrorOccured = true;
  cmSystemTools::Message(message.c_str(),"Error");
}


void cmSystemTools::SetErrorCallback(ErrorCallback f, void* clientData)
{
  s_ErrorCallback = f;
  s_ErrorCallbackClientData = clientData;
}

void cmSystemTools::SetStdoutCallback(StdoutCallback f, void* clientData)
{
  s_StdoutCallback = f;
  s_StdoutCallbackClientData = clientData;
}

void cmSystemTools::Stdout(const char* s)
{
  if(s_StdoutCallback)
    {
    (*s_StdoutCallback)(s, strlen(s), s_StdoutCallbackClientData);
    }
  else
    {
    std::cout << s;
    std::cout.flush();
    }
}

void cmSystemTools::Stdout(const char* s, int length)
{
  if(s_StdoutCallback)
    {
    (*s_StdoutCallback)(s, length, s_StdoutCallbackClientData);
    }
  else
    {
    std::cout.write(s, length);
    std::cout.flush();
    }
}

void cmSystemTools::Message(const char* m1, const char *title)
{
  if(s_DisableMessages)
    {
    return;
    }
  if(s_ErrorCallback)
    {
    (*s_ErrorCallback)(m1, title, s_DisableMessages, s_ErrorCallbackClientData);
    return;
    }
  else
    {
    std::cerr << m1 << std::endl << std::flush;
    }
  
}


void cmSystemTools::ReportLastSystemError(const char* msg)
{
  std::string m = msg;
  m += ": System Error: ";
  m += Superclass::GetLastSystemError();
  cmSystemTools::Error(m.c_str());
}

 
bool cmSystemTools::IsOn(const char* val)
{
  if (!val)
    {
    return false;
    }
  std::basic_string<char> v = val;
  
  for(std::basic_string<char>::iterator c = v.begin();
      c != v.end(); c++)
    {
    *c = toupper(*c);
    }
  return (v == "ON" || v == "1" || v == "YES" || v == "TRUE" || v == "Y");
}

bool cmSystemTools::IsNOTFOUND(const char* val)
{
  int len = strlen(val);
  const char* notfound = "-NOTFOUND";
  const int lenNotFound = 9;
  if(len < lenNotFound-1)
    {
    return false;
    }
  if(len == lenNotFound-1)
    {
    return ( strcmp(val, "NOTFOUND") == 0);
    }
  return ((strncmp((val + (len - lenNotFound)), notfound, lenNotFound) == 0));
}


bool cmSystemTools::IsOff(const char* val)
{
  if (!val || strlen(val) == 0)
    {
    return true;
    }
  std::basic_string<char> v = val;
  
  for(std::basic_string<char>::iterator c = v.begin();
      c != v.end(); c++)
    {
    *c = toupper(*c);
    }
  return (v == "OFF" || v == "0" || v == "NO" || v == "FALSE" || 
          v == "N" || cmSystemTools::IsNOTFOUND(v.c_str()) || v == "IGNORE");
}

std::vector<cmStdString> cmSystemTools::ParseArguments(const char* command)
{
  std::vector<cmStdString> args;
  std::string arg;

  bool win_path = false;

  if ( command[0] != '/' && command[1] == ':' && command[2] == '\\' ||
       command[0] == '\"' && command[1] != '/' && command[2] == ':' && command[3] == '\\' || 
       command[0] == '\'' && command[1] != '/' && command[2] == ':' && command[3] == '\\' || 
       command[0] == '\\' && command[1] == '\\')
    {
    win_path = true;
    }
  // Split the command into an argv array.
  for(const char* c = command; *c;)
    {
    // Skip over whitespace.
    while(*c == ' ' || *c == '\t')
      {
      ++c;
      }
    arg = "";
    if(*c == '"')
      {
      // Parse a quoted argument.
      ++c;
      while(*c && *c != '"')
        {
        arg.append(1, *c);
        ++c;
        }
      if(*c)
        {
        ++c;
        }
      args.push_back(arg);
      }
    else if(*c == '\'')
      {
      // Parse a quoted argument.
      ++c;
      while(*c && *c != '\'')
        {
        arg.append(1, *c);
        ++c;
        }
      if(*c)
        {
        ++c;
        }
      args.push_back(arg);
      }
    else if(*c)
      {
      // Parse an unquoted argument.
      while(*c && *c != ' ' && *c != '\t')
        {
        if(*c == '\\' && !win_path)
          {
          ++c;
          if(*c)
            {
            arg.append(1, *c);
            ++c;
            }
          }
        else
          {
          arg.append(1, *c);
          ++c;
          }
        }
      args.push_back(arg);
      }
    }
  
  return args;
}

bool cmSystemTools::RunSingleCommand(
  const char* command, 
  std::string* output,
  int *retVal, 
  const char* dir,
  bool verbose,
  double timeout)
{
  if(s_DisableRunCommandOutput)
    {
    verbose = false;
    }

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
  if(cmSystemTools::GetRunCommandHideConsole())
    {
    cmsysProcess_SetOption(cp, cmsysProcess_Option_HideWindow, 1);
    }
  cmsysProcess_SetTimeout(cp, timeout);
  cmsysProcess_Execute(cp);
  
  std::vector<char> tempOutput;
  char* data;
  int length;
  if ( output || verbose )
    {
  while(cmsysProcess_WaitForData(cp, &data, &length, 0))
    {
    if(output || verbose)
      {
      // Translate NULL characters in the output into valid text.
      // Visual Studio 7 puts these characters in the output of its
      // build process.
      for(int i=0; i < length; ++i)
        {
        if(data[i] == '\0')
          {
          data[i] = ' ';
          }
        }
      }
    if ( output )
      {
      tempOutput.insert(tempOutput.end(), data, data+length);
      }
    if(verbose)
      {
      cmSystemTools::Stdout(data, length);
      }
    }
    }
  
  cmsysProcess_WaitForExit(cp, 0);
  if ( output && tempOutput.begin() != tempOutput.end())
    {
    output->append(&*tempOutput.begin(), tempOutput.size());
    }
  
  bool result = true;
  if(cmsysProcess_GetState(cp) == cmsysProcess_State_Exited)
    {
    if ( retVal )
      {
      *retVal = cmsysProcess_GetExitValue(cp);
      }
    else
      {
      if ( cmsysProcess_GetExitValue(cp) !=  0 )
        {
        result = false;
        }
      }
    }
  else if(cmsysProcess_GetState(cp) == cmsysProcess_State_Exception)
    {
    const char* exception_str = cmsysProcess_GetExceptionString(cp);
    if ( verbose )
      {
      std::cerr << exception_str << std::endl;
      }
    if ( output )
      {
      output->append(exception_str, strlen(exception_str));
      }
    result = false;
    }
  else if(cmsysProcess_GetState(cp) == cmsysProcess_State_Error)
    {
    const char* error_str = cmsysProcess_GetErrorString(cp);
    if ( verbose )
      {
      std::cerr << error_str << std::endl;
      }
    if ( output )
      {
      output->append(error_str, strlen(error_str));
      }
    result = false;
    }
  else if(cmsysProcess_GetState(cp) == cmsysProcess_State_Expired)
    {
    const char* error_str = "Process terminated due to timeout\n";
    if ( verbose )
      {
      std::cerr << error_str << std::endl;
      }
    if ( output )
      {
      output->append(error_str, strlen(error_str));
      }
    result = false;
    }
  
  cmsysProcess_Delete(cp);
  return result;
}
bool cmSystemTools::RunCommand(const char* command, 
                               std::string& output,
                               const char* dir,
                               bool verbose,
                               int timeout)
{
  int dummy;
  return cmSystemTools::RunCommand(command, output, dummy, 
                                   dir, verbose, timeout);
}

#if defined(WIN32) && !defined(__CYGWIN__)
#include "cmWin32ProcessExecution.h"
// use this for shell commands like echo and dir
bool RunCommandViaWin32(const char* command,
                        const char* dir,
                        std::string& output,
                        int& retVal,
                        bool verbose,
                        int timeout)
{
#if defined(__BORLANDC__)
  return cmWin32ProcessExecution::BorlandRunCommand(command, dir, output, 
                                                    retVal, 
                                                    verbose, timeout, 
                                                    cmSystemTools::GetRunCommandHideConsole());
#else // Visual studio
  ::SetLastError(ERROR_SUCCESS);
  if ( ! command )
    {
    cmSystemTools::Error("No command specified");
    return false;
    }
  cmWin32ProcessExecution resProc;
  if(cmSystemTools::GetRunCommandHideConsole())
    {
    resProc.SetHideWindows(true);
    }
  
  if ( cmSystemTools::GetWindows9xComspecSubstitute() )
    {
    resProc.SetConsoleSpawn(cmSystemTools::GetWindows9xComspecSubstitute() );
    }
  if ( !resProc.StartProcess(command, dir, verbose) )
    {
    output = resProc.GetOutput();
    if(verbose)
      {
      cmSystemTools::Stdout(output.c_str());
      }
    return false;
    }
  resProc.Wait(timeout);
  output = resProc.GetOutput();
  retVal = resProc.GetExitValue();
  return true;
#endif
}

// use this for shell commands like echo and dir
bool RunCommandViaSystem(const char* command,
                         const char* dir,
                         std::string& output,
                         int& retVal,
                         bool verbose)
{  
  std::cout << "@@ " << command << std::endl;

  std::string commandInDir;
  if(dir)
    {
    commandInDir = "cd ";
    commandInDir += cmSystemTools::ConvertToOutputPath(dir);
    commandInDir += " && ";
    commandInDir += command;
    }
  else
    {
    commandInDir = command;
    }
  command = commandInDir.c_str();
  std::string commandToFile = command;
  commandToFile += " > ";
  std::string tempFile;
  tempFile += _tempnam(0, "cmake");

  commandToFile += tempFile;
  retVal = system(commandToFile.c_str());
  std::ifstream fin(tempFile.c_str());
  if(!fin)
    {
    if(verbose)
      {
      std::string errormsg = "RunCommand produced no output: command: \"";
      errormsg += command;
      errormsg += "\"";
      errormsg += "\nOutput file: ";
      errormsg += tempFile;
      cmSystemTools::Error(errormsg.c_str());
      }
    fin.close();
    cmSystemTools::RemoveFile(tempFile.c_str());
    return false;
    }
  bool multiLine = false;
  std::string line;
  while(cmSystemTools::GetLineFromStream(fin, line))
    {
    output += line;
    if(multiLine)
      {
      output += "\n";
      }
    multiLine = true;
    }
  fin.close();
  cmSystemTools::RemoveFile(tempFile.c_str());
  return true;
}

#else // We have popen

bool RunCommandViaPopen(const char* command,
                        const char* dir,
                        std::string& output,
                        int& retVal,
                        bool verbose,
                        int /*timeout*/)
{
  // if only popen worked on windows.....
  std::string commandInDir;
  if(dir)
    {
    commandInDir = "cd \"";
    commandInDir += dir;
    commandInDir += "\" && ";
    commandInDir += command;
    }
  else
    {
    commandInDir = command;
    }
  commandInDir += " 2>&1";
  command = commandInDir.c_str();
  const int BUFFER_SIZE = 4096;
  char buffer[BUFFER_SIZE];
  if(verbose)
    {
    cmSystemTools::Stdout("running ");
    cmSystemTools::Stdout(command);
    cmSystemTools::Stdout("\n");
    }
  fflush(stdout);
  fflush(stderr);
  FILE* cpipe = popen(command, "r");
  if(!cpipe)
    {
    return false;
    }
  fgets(buffer, BUFFER_SIZE, cpipe);
  while(!feof(cpipe))
    {
    if(verbose)
      {
      cmSystemTools::Stdout(buffer);
      }
    output += buffer;
    fgets(buffer, BUFFER_SIZE, cpipe);
    }

  retVal = pclose(cpipe);
  if (WIFEXITED(retVal))
    {
    retVal = WEXITSTATUS(retVal);
    return true;
    }
  if (WIFSIGNALED(retVal))
    {
    retVal = WTERMSIG(retVal);
    cmOStringStream error;
    error << "\nProcess terminated due to ";
    switch (retVal)
      {
#ifdef SIGKILL
      case SIGKILL:
        error << "SIGKILL";
        break;
#endif
#ifdef SIGFPE
      case SIGFPE:
        error << "SIGFPE";
        break;
#endif
#ifdef SIGBUS
      case SIGBUS:
        error << "SIGBUS";
        break;
#endif
#ifdef SIGSEGV
      case SIGSEGV:
        error << "SIGSEGV";
        break;
#endif
      default:
        error << "signal " << retVal;
        break;
      }
    output += error.str();
    }
  return false;
}

#endif  // endif WIN32 not CYGWIN


// run a command unix uses popen (easy)
// windows uses system and ShortPath
bool cmSystemTools::RunCommand(const char* command, 
                               std::string& output,
                               int &retVal, 
                               const char* dir,
                               bool verbose,
                               int timeout)
{
  if(s_DisableRunCommandOutput)
    {
    verbose = false;
    }
  
#if defined(WIN32) && !defined(__CYGWIN__)
  // if the command does not start with a quote, then
  // try to find the program, and if the program can not be
  // found use system to run the command as it must be a built in
  // shell command like echo or dir
  int count = 0;
  if(command[0] == '\"')
    {
    // count the number of quotes
    for(const char* s = command; *s != 0; ++s)
      {
      if(*s == '\"')
        {
        count++;
        if(count > 2)
          {
          break;
          }
        }      
      }
    // if there are more than two double quotes use 
    // GetShortPathName, the cmd.exe program in windows which
    // is used by system fails to execute if there are more than
    // one set of quotes in the arguments
    if(count > 2)
      {
      cmsys::RegularExpression quoted("^\"([^\"]*)\"[ \t](.*)");
      if(quoted.find(command))
        {
        std::string shortCmd;
        std::string cmd = quoted.match(1);
        std::string args = quoted.match(2);
        if(! cmSystemTools::FileExists(cmd.c_str()) )
          {
          shortCmd = cmd;
          }
        else if(!cmSystemTools::GetShortPath(cmd.c_str(), shortCmd))
          {
         cmSystemTools::Error("GetShortPath failed for " , cmd.c_str());
          return false;
          }
        shortCmd += " ";
        shortCmd += args;

        //return RunCommandViaSystem(shortCmd.c_str(), dir, 
        //                           output, retVal, verbose);
        //return WindowsRunCommand(shortCmd.c_str(), dir, 
        //output, retVal, verbose);
        return RunCommandViaWin32(shortCmd.c_str(), dir, 
                                  output, retVal, verbose, timeout);
        }
      else
        {
        cmSystemTools::Error("Could not parse command line with quotes ", 
                             command);
        }
      }
    }
  // if there is only one set of quotes or no quotes then just run the command
  //return RunCommandViaSystem(command, dir, output, retVal, verbose);
  //return WindowsRunCommand(command, dir, output, retVal, verbose);
  return ::RunCommandViaWin32(command, dir, output, retVal, verbose, timeout);
#else
  return ::RunCommandViaPopen(command, dir, output, retVal, verbose, timeout);
#endif
}

bool cmSystemTools::DoesFileExistWithExtensions(
  const char* name,
  const std::vector<std::string>& headerExts)
{
  std::string hname;

  for( std::vector<std::string>::const_iterator ext = headerExts.begin();
       ext != headerExts.end(); ++ext )
    {
    hname = name;
    hname += ".";
    hname += *ext;
    if(cmSystemTools::FileExists(hname.c_str()))
      {
      return true;
      }
    }
  return false;
}

bool cmSystemTools::cmCopyFile(const char* source, const char* destination)
{
  return Superclass::CopyFileAlways(source, destination);
}

bool cmSystemTools::CopyFileIfDifferent(const char* source, 
  const char* destination)
{
  return Superclass::CopyFileIfDifferent(source, destination);
}

void cmSystemTools::Glob(const char *directory, const char *regexp,
                         std::vector<std::string>& files)
{
  cmsys::Directory d;
  cmsys::RegularExpression reg(regexp);
  
  if (d.Load(directory))
    {
    size_t numf;
        unsigned int i;
    numf = d.GetNumberOfFiles();
    for (i = 0; i < numf; i++)
      {
      std::string fname = d.GetFile(i);
      if (reg.find(fname))
        {
        files.push_back(fname);
        }
      }
    }
}


void cmSystemTools::GlobDirs(const char *fullPath,
                             std::vector<std::string>& files)
{
  std::string path = fullPath;
  std::string::size_type pos = path.find("/*");
  if(pos == std::string::npos)
    {
    files.push_back(fullPath);
    return;
    }
  std::string startPath = path.substr(0, pos);
  std::string finishPath = path.substr(pos+2);

  cmsys::Directory d;
  if (d.Load(startPath.c_str()))
    {
    for (unsigned int i = 0; i < d.GetNumberOfFiles(); ++i)
      {
      if((std::string(d.GetFile(i)) != ".")
         && (std::string(d.GetFile(i)) != ".."))
        {
        std::string fname = startPath;
        fname +="/";
        fname += d.GetFile(i);
        if(cmSystemTools::FileIsDirectory(fname.c_str()))
          {
          fname += finishPath;
          cmSystemTools::GlobDirs(fname.c_str(), files);
          }
        }
      }
    }
}


void cmSystemTools::ExpandList(std::vector<std::string> const& arguments, 
                               std::vector<std::string>& newargs)
{
  std::vector<std::string>::const_iterator i;
  for(i = arguments.begin();i != arguments.end(); ++i)
    {
    cmSystemTools::ExpandListArgument(*i, newargs);
    }
}

void cmSystemTools::ExpandListArgument(const std::string& arg,
                                       std::vector<std::string>& newargs,
                                       bool emptyArgs)
{
  // If argument is empty, it is an empty list.
  if(arg.length() == 0 && !emptyArgs)
    {
    return;
    }
  // if there are no ; in the name then just copy the current string
  if(arg.find(';') == std::string::npos)
    {
    newargs.push_back(arg);
    return;
    }
  std::vector<char> newArgVec;
  // Break the string at non-escaped semicolons not nested in [].
  int squareNesting = 0;
  for(const char* c = arg.c_str(); *c; ++c)
    {
    switch(*c)
      {
      case '\\':
        {
        // We only want to allow escaping of semicolons.  Other
        // escapes should not be processed here.
        ++c;
        if(*c == ';')
          {
          newArgVec.push_back(*c);
          }
        else
          {
          newArgVec.push_back('\\');
          if(*c)
            {
            newArgVec.push_back(*c);
            }
          }
        } break;
      case '[':
        {
        ++squareNesting;
        newArgVec.push_back(*c);
        } break;
      case ']':
        {
        --squareNesting;
        newArgVec.push_back(*c);
        } break;
      case ';':
        {
        // Break the string here if we are not nested inside square
        // brackets.
        if(squareNesting == 0)
          {
          if ( newArgVec.size() || emptyArgs )
            {
            // Add the last argument if the string is not empty.
            newArgVec.push_back(0);
            newargs.push_back(&*newArgVec.begin());
            newArgVec.clear();
            }
          }
        else
          {
          newArgVec.push_back(*c);
          }
        } break;
      default:
        {
        // Just append this character.
        newArgVec.push_back(*c);
        } break;
      }
    }
  if ( newArgVec.size() || emptyArgs )
    {
    // Add the last argument if the string is not empty.
    newArgVec.push_back(0);
    newargs.push_back(&*newArgVec.begin());
    }
}

bool cmSystemTools::SimpleGlob(const cmStdString& glob, 
                               std::vector<cmStdString>& files, 
                               int type /* = 0 */)
{
  files.clear();
  if ( glob[glob.size()-1] != '*' )
    {
    return false;
    }
  std::string path = cmSystemTools::GetFilenamePath(glob);
  std::string ppath = cmSystemTools::GetFilenameName(glob);
  ppath = ppath.substr(0, ppath.size()-1);
  if ( path.size() == 0 )
    {
    path = "/";
    }

  bool res = false;
  cmsys::Directory d;
  if (d.Load(path.c_str()))
    {
    for (unsigned int i = 0; i < d.GetNumberOfFiles(); ++i)
      {
      if((std::string(d.GetFile(i)) != ".")
         && (std::string(d.GetFile(i)) != ".."))
        {
        std::string fname = path;
        if ( path[path.size()-1] != '/' )
          {
          fname +="/";
          }
        fname += d.GetFile(i);
        std::string sfname = d.GetFile(i);
        if ( type > 0 && cmSystemTools::FileIsDirectory(fname.c_str()) )
          {
          continue;
          }
        if ( type < 0 && !cmSystemTools::FileIsDirectory(fname.c_str()) )
          {
          continue;
          }
        if ( sfname.size() >= ppath.size() && 
             sfname.substr(0, ppath.size()) == 
             ppath )
          {
          files.push_back(fname);
          res = true;
          }
        }
      }
    }
  return res;
}

cmSystemTools::FileFormat cmSystemTools::GetFileFormat(const char* cext)
{
  if ( ! cext || *cext == 0 )
    {
    return cmSystemTools::NO_FILE_FORMAT;
    }
  //std::string ext = cmSystemTools::LowerCase(cext);
  std::string ext = cext;
  if ( ext == "c" || ext == ".c" ) { return cmSystemTools::C_FILE_FORMAT; }
  if ( 
    ext == "C" || ext == ".C" ||
    ext == "M" || ext == ".M" ||
    ext == "c++" || ext == ".c++" ||
    ext == "cc" || ext == ".cc" ||
    ext == "cpp" || ext == ".cpp" ||
    ext == "cxx" || ext == ".cxx" ||
    ext == "m" || ext == ".m" ||
    ext == "mm" || ext == ".mm"
    ) { return cmSystemTools::CXX_FILE_FORMAT; }
  if ( 
    ext == "f" || ext == ".f" ||
    ext == "F" || ext == ".F" ||
    ext == "f77" || ext == ".f77" ||
    ext == "f90" || ext == ".f90" ||
    ext == "for" || ext == ".for" ||
    ext == "f95" || ext == ".f95" 
    ) { return cmSystemTools::FORTRAN_FILE_FORMAT; }
  if ( ext == "java" || ext == ".java" ) { return cmSystemTools::JAVA_FILE_FORMAT; }
  if ( 
    ext == "H" || ext == ".H" || 
    ext == "h" || ext == ".h" || 
    ext == "h++" || ext == ".h++" ||
    ext == "hm" || ext == ".hm" || 
    ext == "hpp" || ext == ".hpp" || 
    ext == "hxx" || ext == ".hxx" ||
    ext == "in" || ext == ".in" ||
    ext == "txx" || ext == ".txx"
    ) { return cmSystemTools::HEADER_FILE_FORMAT; }
  if ( ext == "rc" || ext == ".rc" ) { return cmSystemTools::RESOURCE_FILE_FORMAT; }
  if ( ext == "def" || ext == ".def" ) { return cmSystemTools::DEFINITION_FILE_FORMAT; }
  if ( ext == "lib" || ext == ".lib" ||
       ext == "a" || ext == ".a") { return cmSystemTools::STATIC_LIBRARY_FILE_FORMAT; }
  if ( ext == "o" || ext == ".o" ||
       ext == "obj" || ext == ".obj") { return cmSystemTools::OBJECT_FILE_FORMAT; }
#ifdef __APPLE__
  if ( ext == "dylib" || ext == ".dylib" ) 
    { return cmSystemTools::SHARED_LIBRARY_FILE_FORMAT; }
  if ( ext == "so" || ext == ".so" || 
       ext == "bundle" || ext == ".bundle" ) 
    { return cmSystemTools::MODULE_FILE_FORMAT; } 
#else // __APPLE__
  if ( ext == "so" || ext == ".so" || 
       ext == "sl" || ext == ".sl" || 
       ext == "dll" || ext == ".dll" ) 
    { return cmSystemTools::SHARED_LIBRARY_FILE_FORMAT; }
#endif // __APPLE__
  return cmSystemTools::UNKNOWN_FILE_FORMAT;
}

bool cmSystemTools::Split(const char* s, std::vector<cmStdString>& l)
{
  std::vector<std::string> temp;
  bool res = Superclass::Split(s, temp);
  for(std::vector<std::string>::const_iterator i = temp.begin();
      i != temp.end(); ++i)
    {
    l.push_back(*i);
    }
  return res;
}

std::string cmSystemTools::ConvertToOutputPath(const char* path)
{
#if defined(_WIN32) && !defined(__CYGWIN__)
  if(s_ForceUnixPaths)
    {
    return cmSystemTools::ConvertToUnixOutputPath(path);
    }
  return cmSystemTools::ConvertToWindowsOutputPath(path);
#else
  return cmSystemTools::ConvertToUnixOutputPath(path);
#endif
}

std::string cmSystemTools::ConvertToRunCommandPath(const char* path)
{
#if defined(_WIN32) && !defined(__CYGWIN__)
  return cmSystemTools::ConvertToWindowsOutputPath(path);
#else
  return cmSystemTools::ConvertToUnixOutputPath(path);
#endif
}

bool cmSystemTools::StringEndsWith(const char* str1, const char* str2)
{
  if ( !str1 || !str2 || strlen(str1) < strlen(str2) )
    {
    return 0;
    }
  return !strncmp(str1 + (strlen(str1)-strlen(str2)), str2, strlen(str2));
}

#if defined(_WIN32) && !defined(__CYGWIN__)
bool cmSystemTools::CreateSymlink(const char*, const char*)
{
  // Should we create a copy here?
  return false;
}
#else
bool cmSystemTools::CreateSymlink(const char* origName, const char* newName)
{
  return (symlink(origName, newName) >= 0);
}
#endif


// compute the relative path from here to there
std::string cmSystemTools::RelativePath(const char* local, const char* remote)
{
  if(!cmSystemTools::FileIsFullPath(local))
    {
    cmSystemTools::Error("RelativePath must be passed a full path to local: ", local);
    }
  if(!cmSystemTools::FileIsFullPath(remote))
    {
    cmSystemTools::Error("RelativePath must be passed a full path to remote: ", remote);
    }
  return cmsys::SystemTools::RelativePath(local, remote);
}

class cmDeletingCharVector : public std::vector<char*>
{
public:
  ~cmDeletingCharVector()
    {
      for(std::vector<char*>::iterator i = this->begin();
          i != this->end(); ++i)
        {
        delete []*i;
        }
    }
};

        
bool cmSystemTools::PutEnv(const char* value)
{ 
  static cmDeletingCharVector localEnvironment;
  char* envVar = new char[strlen(value)+1];
  strcpy(envVar, value);
  int ret = putenv(envVar);
  // save the pointer in the static vector so that it can
  // be deleted on exit
  localEnvironment.push_back(envVar);
  return ret == 0;
}

void cmSystemTools::EnableVSConsoleOutput()
{
  // Visual Studio 8 2005 (devenv.exe or VCExpress.exe) will not
  // display output to the console unless this environment variable is
  // set.  We need it to capture the output of these build tools.
  // Note for future work that one could pass "/out \\.\pipe\NAME" to
  // either of these executables where NAME is created with
  // CreateNamedPipe.  This would bypass the internal buffering of the
  // output and allow it to be captured on the fly.
#ifdef _WIN32
  cmSystemTools::PutEnv("vsconsoleoutput=1");
#endif
}

std::string cmSystemTools::MakeXMLSafe(const char* str)
{
  std::vector<char> result;
  result.reserve(500);
  const char* pos = str;
  for ( ;*pos; ++pos)
    {
    char ch = *pos;
    if ( (ch > 126 || ch < 32) && ch != 9  && ch != 10 && ch != 13 && ch != '\r' )
      {
      char buffer[33];
      sprintf(buffer, "&lt;%d&gt;", (int)ch);
      //sprintf(buffer, "&#x%0x;", (unsigned int)ch);
      result.insert(result.end(), buffer, buffer+strlen(buffer));
      }
    else
      {
      const char* const encodedChars[] = {
        "&amp;",
        "&lt;",
        "&gt;"
      };
      switch ( ch )
        {
        case '&':
          result.insert(result.end(), encodedChars[0], encodedChars[0]+5);
          break;
        case '<':
          result.insert(result.end(), encodedChars[1], encodedChars[1]+4);
          break;
        case '>':
          result.insert(result.end(), encodedChars[2], encodedChars[2]+4);
          break;
        case '\n':
          result.push_back('\n');
          break;
        case '\r': break; // Ignore \r
        default:
          result.push_back(ch);
        }
      }
    }
  if ( result.size() == 0 )
    {
    return "";
    }
  return std::string(&*result.begin(), result.size());
}

bool cmSystemTools::IsPathToFramework(const char* path)
{
  if(cmSystemTools::FileIsFullPath(path))
    {
    std::string libname = path;
    if(libname.find(".framework") == libname.size()+1-sizeof(".framework"))
      {
      return true;
      }
    }
  return false;
}

#if defined(CMAKE_BUILD_WITH_CMAKE)
struct cmSystemToolsGZStruct
{
  gzFile GZFile;
};

extern "C" {
  int cmSystemToolsGZStructOpen(void* call_data, const char *pathname, int oflags, mode_t mode);
  int cmSystemToolsGZStructClose(void* call_data);
  ssize_t cmSystemToolsGZStructRead(void* call_data, void* buf, size_t count);
  ssize_t cmSystemToolsGZStructWrite(void* call_data, const void* buf, size_t count);
}

int cmSystemToolsGZStructOpen(void* call_data, const char *pathname, int oflags, mode_t mode)
{
  const char *gzoflags;
  int fd;

  cmSystemToolsGZStruct* gzf = static_cast<cmSystemToolsGZStruct*>(call_data);

  switch (oflags & O_ACCMODE)
  {
  case O_WRONLY:
    gzoflags = "wb";
    break;
  case O_RDONLY:
    gzoflags = "rb";
    break;
  default:
  case O_RDWR:
    errno = EINVAL;
    return -1;
  }

  fd = open(pathname, oflags, mode);
  if (fd == -1)
    {
    return -1;
    }

#if !defined(_WIN32) || defined(__CYGWIN__)
  if ((oflags & O_CREAT) && fchmod(fd, mode))
    {
    return -1;
    }
#endif

  gzf->GZFile = cm_zlib_gzdopen(fd, gzoflags);
  if (!gzf->GZFile)
  {
    errno = ENOMEM;
    return -1;
  }

  return fd;
}

int cmSystemToolsGZStructClose(void* call_data)
{
  cmSystemToolsGZStruct* gzf = static_cast<cmSystemToolsGZStruct*>(call_data);
  return cm_zlib_gzclose(gzf->GZFile);
}

ssize_t cmSystemToolsGZStructRead(void* call_data, void* buf, size_t count)
{
  cmSystemToolsGZStruct* gzf = static_cast<cmSystemToolsGZStruct*>(call_data);
  return cm_zlib_gzread(gzf->GZFile, buf, count);
}

ssize_t cmSystemToolsGZStructWrite(void* call_data, const void* buf, size_t count)
{
  cmSystemToolsGZStruct* gzf = static_cast<cmSystemToolsGZStruct*>(call_data);
  return cm_zlib_gzwrite(gzf->GZFile, (void*)buf, count);
}

#endif

bool cmSystemTools::CreateTar(const char* outFileName, const std::vector<cmStdString>& files, bool gzip, bool verbose)
{
#if defined(CMAKE_BUILD_WITH_CMAKE)
  TAR *t;
  char buf[TAR_MAXPATHLEN];
  char pathname[TAR_MAXPATHLEN];
  cmSystemToolsGZStruct gzs;

  tartype_t gztype = {
    (openfunc_t)cmSystemToolsGZStructOpen,
    (closefunc_t)cmSystemToolsGZStructClose,
    (readfunc_t)cmSystemToolsGZStructRead,
    (writefunc_t)cmSystemToolsGZStructWrite,
    &gzs
  };

  // Ok, this libtar is not const safe. for now use auto_ptr hack
  char* realName = new char[ strlen(outFileName) + 1 ];
  std::auto_ptr<char> realNamePtr(realName);
  strcpy(realName, outFileName);
  if (tar_open(&t, realName,
      (gzip? &gztype : NULL),
      O_WRONLY | O_CREAT, 0644,
      (verbose?TAR_VERBOSE:0)
      | 0) == -1)
    {
    cmSystemTools::Error("Problem with tar_open(): ", strerror(errno));
    return false;
    }

  std::vector<cmStdString>::const_iterator it;
  for (it = files.begin(); it != files.end(); ++ it )
    {
    strncpy(pathname, it->c_str(), sizeof(pathname));
    pathname[sizeof(pathname)-1] = 0;
    strncpy(buf, pathname, sizeof(buf));
    buf[sizeof(buf)-1] = 0;
    if (tar_append_tree(t, buf, pathname) != 0)
      {
      cmOStringStream ostr;
      ostr << "Problem with tar_append_tree(\"" << buf << "\", \"" << pathname << "\"): "
        << strerror(errno);
      cmSystemTools::Error(ostr.str().c_str());
      tar_close(t);
      return false;
      }
    }

  if (tar_append_eof(t) != 0)
    {
    cmSystemTools::Error("Problem with tar_append_eof(): ", strerror(errno));
    tar_close(t);
    return false;
    }

  if (tar_close(t) != 0)
    {
    cmSystemTools::Error("Problem with tar_close(): ", strerror(errno));
    return false;
    }
  return true;
#else
  return false;
#endif
}

bool cmSystemTools::ExtractTar(const char* outFileName, const std::vector<cmStdString>& files, bool gzip, bool verbose)
{
  (void)files;
#if defined(CMAKE_BUILD_WITH_CMAKE)
  TAR *t;
  cmSystemToolsGZStruct gzs;

  tartype_t gztype = {
    cmSystemToolsGZStructOpen,
    cmSystemToolsGZStructClose,
    cmSystemToolsGZStructRead,
    cmSystemToolsGZStructWrite,
    &gzs
  };

  // Ok, this libtar is not const safe. for now use auto_ptr hack
  char* realName = new char[ strlen(outFileName) + 1 ];
  std::auto_ptr<char> realNamePtr(realName);
  strcpy(realName, outFileName);
  if (tar_open(&t, realName,
      (gzip? &gztype : NULL),
      O_RDONLY
#ifdef _WIN32
      | O_BINARY
#endif
      , 0,
      (verbose?TAR_VERBOSE:0)
      | 0) == -1)
    {
    cmSystemTools::Error("Problem with tar_open(): ", strerror(errno));
    return false;
    }

  if (tar_extract_all(t, 0) != 0)
  {
    cmSystemTools::Error("Problem with tar_extract_all(): ", strerror(errno));
    return false;
  }

  if (tar_close(t) != 0)
    {
    cmSystemTools::Error("Problem with tar_close(): ", strerror(errno));
    return false;
    }
  return true;
#else
  return false;
#endif
}

bool cmSystemTools::ListTar(const char* outFileName, std::vector<cmStdString>& files, bool gzip, bool verbose)
{
#if defined(CMAKE_BUILD_WITH_CMAKE)
  TAR *t;
  cmSystemToolsGZStruct gzs;

  tartype_t gztype = {
    cmSystemToolsGZStructOpen,
    cmSystemToolsGZStructClose,
    cmSystemToolsGZStructRead,
    cmSystemToolsGZStructWrite,
    &gzs
  };

  // Ok, this libtar is not const safe. for now use auto_ptr hack
  char* realName = new char[ strlen(outFileName) + 1 ];
  std::auto_ptr<char> realNamePtr(realName);
  strcpy(realName, outFileName);
  if (tar_open(&t, realName,
      (gzip? &gztype : NULL),
      O_RDONLY
#ifdef _WIN32
      | O_BINARY
#endif
      , 0,
      (verbose?TAR_VERBOSE:0)
      | 0) == -1)
    {
    cmSystemTools::Error("Problem with tar_open(): ", strerror(errno));
    return false;
    }

  while ((th_read(t)) == 0)
  {
    const char* filename = th_get_pathname(t);
    files.push_back(filename);
   
    if ( verbose )
      {
      th_print_long_ls(t);
      }
    else
      {
      std::cout << filename << std::endl;
      }

#ifdef DEBUG
    th_print(t);
#endif
    if (TH_ISREG(t) && tar_skip_regfile(t) != 0)
      {
      cmSystemTools::Error("Problem with tar_skip_regfile(): ", strerror(errno));
      return false;
      }
  }

  if (tar_close(t) != 0)
    {
    cmSystemTools::Error("Problem with tar_close(): ", strerror(errno));
    return false;
    }
  return true;
#else
  return false;
#endif
}
