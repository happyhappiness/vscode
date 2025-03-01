/*============================================================================
  KWSys - Kitware System Library
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "kwsysPrivate.h"
#include KWSYS_HEADER(Process.h)
#include KWSYS_HEADER(Encoding.h)

/* Work-around CMake dependency scanning limitation.  This must
   duplicate the above list of headers.  */
#if 0
# include "Process.h.in"
# include "Encoding_c.h.in"
#endif

/*

Implementation for Windows

On windows, a thread is created to wait for data on each pipe.  The
threads are synchronized with the main thread to simulate the use of
a UNIX-style select system call.

*/

#ifdef _MSC_VER
#pragma warning (push, 1)
#endif
#include <windows.h> /* Windows API */
#if defined(_MSC_VER) && _MSC_VER >= 1800
# define KWSYS_WINDOWS_DEPRECATED_GetVersionEx
#endif
#include <string.h>  /* strlen, strdup */
#include <stdio.h>   /* sprintf */
#include <io.h>      /* _unlink */
#ifdef __WATCOMC__
#define _unlink unlink
#endif

#ifndef _MAX_FNAME
#define _MAX_FNAME 4096
#endif
#ifndef _MAX_PATH
#define _MAX_PATH 4096
#endif

#ifdef _MSC_VER
#pragma warning (pop)
#pragma warning (disable: 4514)
#pragma warning (disable: 4706)
#endif

#if defined(__BORLANDC__)
# pragma warn -8004 /* assigned a value that is never used  */
# pragma warn -8060 /* Assignment inside if() condition.  */
#endif

/* There are pipes for the process pipeline's stdout and stderr.  */
#define KWSYSPE_PIPE_COUNT 2
#define KWSYSPE_PIPE_STDOUT 0
#define KWSYSPE_PIPE_STDERR 1

/* The maximum amount to read from a pipe at a time.  */
#define KWSYSPE_PIPE_BUFFER_SIZE 1024

/* Debug output macro.  */
#if 0
# define KWSYSPE_DEBUG(x) \
( \
  (void*)cp == (void*)0x00226DE0? \
  ( \
    fprintf(stderr, "%d/%p/%d ", (int)GetCurrentProcessId(), cp, __LINE__), \
    fprintf x, \
    fflush(stderr), \
    1 \
  ) : (1) \
)
#else
# define KWSYSPE_DEBUG(x) (void)1
#endif

typedef LARGE_INTEGER kwsysProcessTime;

typedef struct kwsysProcessCreateInformation_s
{
  /* Windows child startup control data.  */
  STARTUPINFOW StartupInfo;

  /* Original handles before making inherited duplicates.  */
  HANDLE hStdInput;
  HANDLE hStdOutput;
  HANDLE hStdError;
} kwsysProcessCreateInformation;


/*--------------------------------------------------------------------------*/
typedef struct kwsysProcessPipeData_s kwsysProcessPipeData;
static DWORD WINAPI kwsysProcessPipeThreadRead(LPVOID ptd);
static void kwsysProcessPipeThreadReadPipe(kwsysProcess* cp,
                                           kwsysProcessPipeData* td);
static DWORD WINAPI kwsysProcessPipeThreadWake(LPVOID ptd);
static void kwsysProcessPipeThreadWakePipe(kwsysProcess* cp,
                                           kwsysProcessPipeData* td);
static int kwsysProcessInitialize(kwsysProcess* cp);
static int kwsysProcessCreate(kwsysProcess* cp, int index,
                              kwsysProcessCreateInformation* si);
static void kwsysProcessDestroy(kwsysProcess* cp, int event);
static int kwsysProcessSetupOutputPipeFile(PHANDLE handle, const char* name);
static void kwsysProcessSetupSharedPipe(DWORD nStdHandle, PHANDLE handle);
static void kwsysProcessSetupPipeNative(HANDLE native, PHANDLE handle);
static void kwsysProcessCleanupHandle(PHANDLE h);
static void kwsysProcessCleanup(kwsysProcess* cp, int error);
static void kwsysProcessCleanErrorMessage(kwsysProcess* cp);
static int kwsysProcessGetTimeoutTime(kwsysProcess* cp, double* userTimeout,
                                      kwsysProcessTime* timeoutTime);
static int kwsysProcessGetTimeoutLeft(kwsysProcessTime* timeoutTime,
                                      double* userTimeout,
                                      kwsysProcessTime* timeoutLength);
static kwsysProcessTime kwsysProcessTimeGetCurrent(void);
static DWORD kwsysProcessTimeToDWORD(kwsysProcessTime t);
static double kwsysProcessTimeToDouble(kwsysProcessTime t);
static kwsysProcessTime kwsysProcessTimeFromDouble(double d);
static int kwsysProcessTimeLess(kwsysProcessTime in1, kwsysProcessTime in2);
static kwsysProcessTime kwsysProcessTimeAdd(kwsysProcessTime in1, kwsysProcessTime in2);
static kwsysProcessTime kwsysProcessTimeSubtract(kwsysProcessTime in1, kwsysProcessTime in2);
static void kwsysProcessSetExitException(kwsysProcess* cp, int code);
static void kwsysProcessKillTree(int pid);
static void kwsysProcessDisablePipeThreads(kwsysProcess* cp);

/*--------------------------------------------------------------------------*/
/* A structure containing synchronization data for each thread.  */
typedef struct kwsysProcessPipeSync_s kwsysProcessPipeSync;
struct kwsysProcessPipeSync_s
{
  /* Handle to the thread.  */
  HANDLE Thread;

  /* Semaphore indicating to the thread that a process has started.  */
  HANDLE Ready;

  /* Semaphore indicating to the thread that it should begin work.  */
  HANDLE Go;

  /* Semaphore indicating thread has reset for another process.  */
  HANDLE Reset;
};

/*--------------------------------------------------------------------------*/
/* A structure containing data for each pipe's threads.  */
struct kwsysProcessPipeData_s
{
  /* ------------- Data managed per instance of kwsysProcess ------------- */

  /* Synchronization data for reading thread.  */
  kwsysProcessPipeSync Reader;

  /* Synchronization data for waking thread.  */
  kwsysProcessPipeSync Waker;

  /* Index of this pipe.  */
  int Index;

  /* The kwsysProcess instance owning this pipe.  */
  kwsysProcess* Process;

  /* ------------- Data managed per call to Execute ------------- */

  /* Buffer for data read in this pipe's thread.  */
  char DataBuffer[KWSYSPE_PIPE_BUFFER_SIZE];

  /* The length of the data stored in the buffer.  */
  DWORD DataLength;

  /* Whether the pipe has been closed.  */
  int Closed;

  /* Handle for the read end of this pipe. */
  HANDLE Read;

  /* Handle for the write end of this pipe. */
  HANDLE Write;
};

/*--------------------------------------------------------------------------*/
/* Structure containing data used to implement the child's execution.  */
struct kwsysProcess_s
{
  /* ------------- Data managed per instance of kwsysProcess ------------- */

  /* The status of the process structure.  */
  int State;

  /* The command lines to execute.  */
  wchar_t** Commands;
  int NumberOfCommands;

  /* The exit code of each command.  */
  DWORD* CommandExitCodes;

  /* The working directory for the child process.  */
  wchar_t* WorkingDirectory;

  /* Whether to create the child as a detached process.  */
  int OptionDetach;

  /* Whether the child was created as a detached process.  */
  int Detached;

  /* Whether to hide the child process's window.  */
  int HideWindow;

  /* Whether to treat command lines as verbatim.  */
  int Verbatim;

  /* Whether to merge stdout/stderr of the child.  */
  int MergeOutput;

  /* Mutex to protect the shared index used by threads to report data.  */
  HANDLE SharedIndexMutex;

  /* Semaphore used by threads to signal data ready.  */
  HANDLE Full;

  /* Whether we are currently deleting this kwsysProcess instance.  */
  int Deleting;

  /* Data specific to each pipe and its thread.  */
  kwsysProcessPipeData Pipe[KWSYSPE_PIPE_COUNT];

  /* Name of files to which stdin and stdout pipes are attached.  */
  char* PipeFileSTDIN;
  char* PipeFileSTDOUT;
  char* PipeFileSTDERR;

  /* Whether each pipe is shared with the parent process.  */
  int PipeSharedSTDIN;
  int PipeSharedSTDOUT;
  int PipeSharedSTDERR;

  /* Native pipes provided by the user.  */
  HANDLE PipeNativeSTDIN[2];
  HANDLE PipeNativeSTDOUT[2];
  HANDLE PipeNativeSTDERR[2];

  /* ------------- Data managed per call to Execute ------------- */

  /* The exceptional behavior that terminated the process, if any.  */
  int ExitException;

  /* The process exit code.  */
  DWORD ExitCode;

  /* The process return code, if any.  */
  int ExitValue;

  /* Index of last pipe to report data, if any.  */
  int CurrentIndex;

  /* Index shared by threads to report data.  */
  int SharedIndex;

  /* The timeout length.  */
  double Timeout;

  /* Time at which the child started.  */
  kwsysProcessTime StartTime;

  /* Time at which the child will timeout.  Negative for no timeout.  */
  kwsysProcessTime TimeoutTime;

  /* Flag for whether the process was killed.  */
  int Killed;

  /* Flag for whether the timeout expired.  */
  int TimeoutExpired;

  /* Flag for whether the process has terminated.  */
  int Terminated;

  /* The number of pipes still open during execution and while waiting
     for pipes to close after process termination.  */
  int PipesLeft;

  /* Buffer for error messages.  */
  char ErrorMessage[KWSYSPE_PIPE_BUFFER_SIZE+1];

  /* Description for the ExitException.  */
  char ExitExceptionString[KWSYSPE_PIPE_BUFFER_SIZE+1];

  /* Windows process information data.  */
  PROCESS_INFORMATION* ProcessInformation;

  /* Data and process termination events for which to wait.  */
  PHANDLE ProcessEvents;
  int ProcessEventsLength;

  /* Real working directory of our own process.  */
  DWORD RealWorkingDirectoryLength;
  wchar_t* RealWorkingDirectory;

  /* Own handles for the child's ends of the pipes in the parent process.
     Used temporarily during process creation.  */
  HANDLE PipeChildStd[3];
};

/*--------------------------------------------------------------------------*/
kwsysProcess* kwsysProcess_New(void)
{
  int i;

  /* Process control structure.  */
  kwsysProcess* cp;

  /* Windows version number data.  */
  OSVERSIONINFO osv;

  /* Allocate a process control structure.  */
  cp = (kwsysProcess*)malloc(sizeof(kwsysProcess));
  if(!cp)
    {
    /* Could not allocate memory for the control structure.  */
    return 0;
    }
  ZeroMemory(cp, sizeof(*cp));

  /* Share stdin with the parent process by default.  */
  cp->PipeSharedSTDIN = 1;

  /* Set initial status.  */
  cp->State = kwsysProcess_State_Starting;

  /* Choose a method of running the child based on version of
     windows.  */
  ZeroMemory(&osv, sizeof(osv));
  osv.dwOSVersionInfoSize = sizeof(osv);
#ifdef KWSYS_WINDOWS_DEPRECATED_GetVersionEx
# pragma warning (push)
# ifdef __INTEL_COMPILER
#  pragma warning (disable:1478)
# else
#  pragma warning (disable:4996)
# endif
#endif
  GetVersionEx(&osv);
#ifdef KWSYS_WINDOWS_DEPRECATED_GetVersionEx
# pragma warning (pop)
#endif
  if(osv.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
    {
    /* Win9x no longer supported.  */
    kwsysProcess_Delete(cp);
    return 0;
    }

  /* Initially no thread owns the mutex.  Initialize semaphore to 1.  */
  if(!(cp->SharedIndexMutex = CreateSemaphore(0, 1, 1, 0)))
    {
    kwsysProcess_Delete(cp);
    return 0;
    }

  /* Initially no data are available.  Initialize semaphore to 0.  */
  if(!(cp->Full = CreateSemaphore(0, 0, 1, 0)))
    {
    kwsysProcess_Delete(cp);
    return 0;
    }

  /* Create the thread to read each pipe.  */
  for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
    {
    DWORD dummy=0;

    /* Assign the thread its index.  */
    cp->Pipe[i].Index = i;

    /* Give the thread a pointer back to the kwsysProcess instance.  */
    cp->Pipe[i].Process = cp;

    /* No process is yet running.  Initialize semaphore to 0.  */
    if(!(cp->Pipe[i].Reader.Ready = CreateSemaphore(0, 0, 1, 0)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }

    /* The pipe is not yet reset.  Initialize semaphore to 0.  */
    if(!(cp->Pipe[i].Reader.Reset = CreateSemaphore(0, 0, 1, 0)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }

    /* The thread's buffer is initially empty.  Initialize semaphore to 1.  */
    if(!(cp->Pipe[i].Reader.Go = CreateSemaphore(0, 1, 1, 0)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }

    /* Create the reading thread.  It will block immediately.  The
       thread will not make deeply nested calls, so we need only a
       small stack.  */
    if(!(cp->Pipe[i].Reader.Thread = CreateThread(0, 1024,
                                                  kwsysProcessPipeThreadRead,
                                                  &cp->Pipe[i], 0, &dummy)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }

    /* No process is yet running.  Initialize semaphore to 0.  */
    if(!(cp->Pipe[i].Waker.Ready = CreateSemaphore(0, 0, 1, 0)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }

    /* The pipe is not yet reset.  Initialize semaphore to 0.  */
    if(!(cp->Pipe[i].Waker.Reset = CreateSemaphore(0, 0, 1, 0)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }

    /* The waker should not wake immediately.  Initialize semaphore to 0.  */
    if(!(cp->Pipe[i].Waker.Go = CreateSemaphore(0, 0, 1, 0)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }

    /* Create the waking thread.  It will block immediately.  The
       thread will not make deeply nested calls, so we need only a
       small stack.  */
    if(!(cp->Pipe[i].Waker.Thread = CreateThread(0, 1024,
                                                 kwsysProcessPipeThreadWake,
                                                 &cp->Pipe[i], 0, &dummy)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }
    }
  for(i=0; i < 3; ++i)
    {
    cp->PipeChildStd[i] = INVALID_HANDLE_VALUE;
    }

  return cp;
}

/*--------------------------------------------------------------------------*/
void kwsysProcess_Delete(kwsysProcess* cp)
{
  int i;

  /* Make sure we have an instance.  */
  if(!cp)
    {
    return;
    }

  /* If the process is executing, wait for it to finish.  */
  if(cp->State == kwsysProcess_State_Executing)
    {
    if(cp->Detached)
      {
      kwsysProcess_Disown(cp);
      }
    else
      {
      kwsysProcess_WaitForExit(cp, 0);
      }
    }

  /* We are deleting the kwsysProcess instance.  */
  cp->Deleting = 1;

  /* Terminate each of the threads.  */
  for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
    {
    /* Terminate this reading thread.  */
    if(cp->Pipe[i].Reader.Thread)
      {
      /* Signal the thread we are ready for it.  It will terminate
         immediately since Deleting is set.  */
      ReleaseSemaphore(cp->Pipe[i].Reader.Ready, 1, 0);

      /* Wait for the thread to exit.  */
      WaitForSingleObject(cp->Pipe[i].Reader.Thread, INFINITE);

      /* Close the handle to the thread. */
      kwsysProcessCleanupHandle(&cp->Pipe[i].Reader.Thread);
      }

    /* Terminate this waking thread.  */
    if(cp->Pipe[i].Waker.Thread)
      {
      /* Signal the thread we are ready for it.  It will terminate
         immediately since Deleting is set.  */
      ReleaseSemaphore(cp->Pipe[i].Waker.Ready, 1, 0);

      /* Wait for the thread to exit.  */
      WaitForSingleObject(cp->Pipe[i].Waker.Thread, INFINITE);

      /* Close the handle to the thread. */
      kwsysProcessCleanupHandle(&cp->Pipe[i].Waker.Thread);
      }

    /* Cleanup the pipe's semaphores.  */
    kwsysProcessCleanupHandle(&cp->Pipe[i].Reader.Ready);
    kwsysProcessCleanupHandle(&cp->Pipe[i].Reader.Go);
    kwsysProcessCleanupHandle(&cp->Pipe[i].Reader.Reset);
    kwsysProcessCleanupHandle(&cp->Pipe[i].Waker.Ready);
    kwsysProcessCleanupHandle(&cp->Pipe[i].Waker.Go);
    kwsysProcessCleanupHandle(&cp->Pipe[i].Waker.Reset);
    }

  /* Close the shared semaphores.  */
  kwsysProcessCleanupHandle(&cp->SharedIndexMutex);
  kwsysProcessCleanupHandle(&cp->Full);

  /* Free memory.  */
  kwsysProcess_SetCommand(cp, 0);
  kwsysProcess_SetWorkingDirectory(cp, 0);
  kwsysProcess_SetPipeFile(cp, kwsysProcess_Pipe_STDIN, 0);
  kwsysProcess_SetPipeFile(cp, kwsysProcess_Pipe_STDOUT, 0);
  kwsysProcess_SetPipeFile(cp, kwsysProcess_Pipe_STDERR, 0);
  if(cp->CommandExitCodes)
    {
    free(cp->CommandExitCodes);
    }
  free(cp);
}

/*--------------------------------------------------------------------------*/
int kwsysProcess_SetCommand(kwsysProcess* cp, char const* const* command)
{
  int i;
  if(!cp)
    {
    return 0;
    }
  for(i=0; i < cp->NumberOfCommands; ++i)
    {
    free(cp->Commands[i]);
    }
  cp->NumberOfCommands = 0;
  if(cp->Commands)
    {
    free(cp->Commands);
    cp->Commands = 0;
    }
  if(command)
    {
    return kwsysProcess_AddCommand(cp, command);
    }
  return 1;
}

/*--------------------------------------------------------------------------*/
int kwsysProcess_AddCommand(kwsysProcess* cp, char const* const* command)
{
  int newNumberOfCommands;
  wchar_t** newCommands;

  /* Make sure we have a command to add.  */
  if(!cp || !command || !*command)
    {
    return 0;
    }


  /* Allocate a new array for command pointers.  */
  newNumberOfCommands = cp->NumberOfCommands + 1;
  if(!(newCommands = (wchar_t**)malloc(sizeof(wchar_t*) * newNumberOfCommands)))
    {
    /* Out of memory.  */
    return 0;
    }

  /* Copy any existing commands into the new array.  */
  {
  int i;
  for(i=0; i < cp->NumberOfCommands; ++i)
    {
    newCommands[i] = cp->Commands[i];
    }
  }

  if (cp->Verbatim)
    {
    /* Copy the verbatim command line into the buffer.  */
    newCommands[cp->NumberOfCommands] = kwsysEncoding_DupToWide(*command);
    }
  else
    {
    /* Encode the arguments so CommandLineToArgvW can decode
       them from the command line string in the child.  */
    char buffer[32768]; /* CreateProcess max command-line length.  */
    char* end = buffer + sizeof(buffer);
    char* out = buffer;
    char const* const* a;
    for (a = command; *a; ++a)
      {
      int quote = !**a; /* Quote the empty string.  */
      int slashes = 0;
      char const* c;
      if (a != command && out != end) { *out++ = ' '; }
      for (c = *a; !quote && *c; ++c)
        { quote = (*c == ' ' || *c == '\t'); }
      if (quote && out != end) { *out++ = '"'; }
      for (c = *a; *c; ++c)
        {
        if (*c == '\\')
          {
          ++slashes;
          }
        else
          {
          if (*c == '"')
            {
            // Add n+1 backslashes to total 2n+1 before internal '"'.
            while(slashes-- >= 0 && out != end) { *out++ = '\\'; }
            }
          slashes = 0;
          }
        if (out != end) { *out++ = *c; }
        }
      if (quote)
        {
        // Add n backslashes to total 2n before ending '"'.
        while (slashes-- > 0 && out != end) { *out++ = '\\'; }
        if (out != end) { *out++ = '"'; }
        }
      }
    if(out != end)
      {
      *out = '\0';
      newCommands[cp->NumberOfCommands] = kwsysEncoding_DupToWide(buffer);
      }
    else
      {
      newCommands[cp->NumberOfCommands] = 0;
      }
    }
  if (!newCommands[cp->NumberOfCommands])
    {
    /* Out of memory or command line too long.  */
    free(newCommands);
    return 0;
    }

  /* Save the new array of commands.  */
  free(cp->Commands);
  cp->Commands = newCommands;
  cp->NumberOfCommands = newNumberOfCommands;
  return 1;
}

/*--------------------------------------------------------------------------*/
void kwsysProcess_SetTimeout(kwsysProcess* cp, double timeout)
{
  if(!cp)
    {
    return;
    }
  cp->Timeout = timeout;
  if(cp->Timeout < 0)
    {
    cp->Timeout = 0;
    }
}

/*--------------------------------------------------------------------------*/
int kwsysProcess_SetWorkingDirectory(kwsysProcess* cp, const char* dir)
{
  if(!cp)
    {
    return 0;
    }
  if(cp->WorkingDirectory)
    {
    free(cp->WorkingDirectory);
    cp->WorkingDirectory = 0;
    }
  if(dir && dir[0])
    {
    wchar_t* wdir = kwsysEncoding_DupToWide(dir);
    /* We must convert the working directory to a full path.  */
    DWORD length = GetFullPathNameW(wdir, 0, 0, 0);
    if(length > 0)
      {
      wchar_t* work_dir = malloc(length*sizeof(wchar_t));
      if(!work_dir)
        {
        free(wdir);
        return 0;
        }
      if(!GetFullPathNameW(wdir, length, work_dir, 0))
        {
        free(work_dir);
        free(wdir);
        return 0;
        }
      cp->WorkingDirectory = work_dir;
      }
    free(wdir);
    }
  return 1;
}

/*--------------------------------------------------------------------------*/
int kwsysProcess_SetPipeFile(kwsysProcess* cp, int pipe, const char* file)
{
  char** pfile;
  if(!cp)
    {
    return 0;
    }
  switch(pipe)
    {
    case kwsysProcess_Pipe_STDIN: pfile = &cp->PipeFileSTDIN; break;
    case kwsysProcess_Pipe_STDOUT: pfile = &cp->PipeFileSTDOUT; break;
    case kwsysProcess_Pipe_STDERR: pfile = &cp->PipeFileSTDERR; break;
    default: return 0;
    }
  if(*pfile)
    {
    free(*pfile);
    *pfile = 0;
    }
  if(file)
    {
    *pfile = (char*)malloc(strlen(file)+1);
    if(!*pfile)
      {
      return 0;
      }
    strcpy(*pfile, file);
    }

  /* If we are redirecting the pipe, do not share it or use a native
     pipe.  */
  if(*pfile)
    {
    kwsysProcess_SetPipeNative(cp, pipe, 0);
    kwsysProcess_SetPipeShared(cp, pipe, 0);
    }

  return 1;
}

/*--------------------------------------------------------------------------*/
void kwsysProcess_SetPipeShared(kwsysProcess* cp, int pipe, int shared)
{
  if(!cp)
    {
    return;
    }

  switch(pipe)
    {
    case kwsysProcess_Pipe_STDIN: cp->PipeSharedSTDIN = shared?1:0; break;
    case kwsysProcess_Pipe_STDOUT: cp->PipeSharedSTDOUT = shared?1:0; break;
    case kwsysProcess_Pipe_STDERR: cp->PipeSharedSTDERR = shared?1:0; break;
    default: return;
    }

  /* If we are sharing the pipe, do not redirect it to a file or use a
     native pipe.  */
  if(shared)
    {
    kwsysProcess_SetPipeFile(cp, pipe, 0);
    kwsysProcess_SetPipeNative(cp, pipe, 0);
    }
}

/*--------------------------------------------------------------------------*/
void kwsysProcess_SetPipeNative(kwsysProcess* cp, int pipe, HANDLE p[2])
{
  HANDLE* pPipeNative = 0;

  if(!cp)
    {
    return;
    }

  switch(pipe)
    {
    case kwsysProcess_Pipe_STDIN: pPipeNative = cp->PipeNativeSTDIN; break;
    case kwsysProcess_Pipe_STDOUT: pPipeNative = cp->PipeNativeSTDOUT; break;
    case kwsysProcess_Pipe_STDERR: pPipeNative = cp->PipeNativeSTDERR; break;
    default: return;
    }

  /* Copy the native pipe handles provided.  */
  if(p)
    {
    pPipeNative[0] = p[0];
    pPipeNative[1] = p[1];
    }
  else
    {
    pPipeNative[0] = 0;
    pPipeNative[1] = 0;
    }

  /* If we are using a native pipe, do not share it or redirect it to
     a file.  */
  if(p)
    {
    kwsysProcess_SetPipeFile(cp, pipe, 0);
    kwsysProcess_SetPipeShared(cp, pipe, 0);
    }
}

/*--------------------------------------------------------------------------*/
int kwsysProcess_GetOption(kwsysProcess* cp, int optionId)
{
  if(!cp)
    {
    return 0;
    }

  switch(optionId)
    {
    case kwsysProcess_Option_Detach: return cp->OptionDetach;
    case kwsysProcess_Option_HideWindow: return cp->HideWindow;
    case kwsysProcess_Option_MergeOutput: return cp->MergeOutput;
    case kwsysProcess_Option_Verbatim: return cp->Verbatim;
    default: return 0;
    }
}

/*--------------------------------------------------------------------------*/
void kwsysProcess_SetOption(kwsysProcess* cp, int optionId, int value)
{
  if(!cp)
    {
    return;
    }

  switch(optionId)
    {
    case kwsysProcess_Option_Detach: cp->OptionDetach = value; break;
    case kwsysProcess_Option_HideWindow: cp->HideWindow = value; break;
    case kwsysProcess_Option_MergeOutput: cp->MergeOutput = value; break;
    case kwsysProcess_Option_Verbatim: cp->Verbatim = value; break;
    default: break;
    }
}

/*--------------------------------------------------------------------------*/
int kwsysProcess_GetState(kwsysProcess* cp)
{
  return cp? cp->State : kwsysProcess_State_Error;
}

/*--------------------------------------------------------------------------*/
int kwsysProcess_GetExitException(kwsysProcess* cp)
{
  return cp? cp->ExitException : kwsysProcess_Exception_Other;
}

/*--------------------------------------------------------------------------*/
int kwsysProcess_GetExitValue(kwsysProcess* cp)
{
  return cp? cp->ExitValue : -1;
}

/*--------------------------------------------------------------------------*/
int kwsysProcess_GetExitCode(kwsysProcess* cp)
{
  return cp? cp->ExitCode : 0;
}

/*--------------------------------------------------------------------------*/
const char* kwsysProcess_GetErrorString(kwsysProcess* cp)
{
  if(!cp)
    {
    return "Process management structure could not be allocated";
    }
  else if(cp->State == kwsysProcess_State_Error)
    {
    return cp->ErrorMessage;
    }
  return "Success";
}

/*--------------------------------------------------------------------------*/
const char* kwsysProcess_GetExceptionString(kwsysProcess* cp)
{
  if(!cp)
    {
    return "GetExceptionString called with NULL process management structure";
    }
  else if(cp->State == kwsysProcess_State_Exception)
    {
    return cp->ExitExceptionString;
    }
  return "No exception";
}

/*--------------------------------------------------------------------------*/
void kwsysProcess_Execute(kwsysProcess* cp)
{
  int i;

  /* Do not execute a second time.  */
  if(!cp || cp->State == kwsysProcess_State_Executing)
    {
    return;
    }

  /* Make sure we have something to run.  */
  if(cp->NumberOfCommands < 1)
    {
    strcpy(cp->ErrorMessage, "No command");
    cp->State = kwsysProcess_State_Error;
    return;
    }

  /* Initialize the control structure for a new process.  */
  if(!kwsysProcessInitialize(cp))
    {
    strcpy(cp->ErrorMessage, "Out of memory");
    cp->State = kwsysProcess_State_Error;
    return;
    }

  /* Save the real working directory of this process and change to
     the working directory for the child processes.  This is needed
     to make pipe file paths evaluate correctly.  */
  if(cp->WorkingDirectory)
    {
    if(!GetCurrentDirectoryW(cp->RealWorkingDirectoryLength,
                            cp->RealWorkingDirectory))
      {
      kwsysProcessCleanup(cp, 1);
      return;
      }
    SetCurrentDirectoryW(cp->WorkingDirectory);
    }


  /* Setup the stdin pipe for the first process.  */
  if(cp->PipeFileSTDIN)
    {
    /* Create a handle to read a file for stdin.  */
    wchar_t* wstdin = kwsysEncoding_DupToWide(cp->PipeFileSTDIN);
    cp->PipeChildStd[0] =
      CreateFileW(wstdin, GENERIC_READ|GENERIC_WRITE,
                  FILE_SHARE_READ|FILE_SHARE_WRITE,
                  0, OPEN_EXISTING, 0, 0);
    free(wstdin);
    if(cp->PipeChildStd[0] == INVALID_HANDLE_VALUE)
      {
      kwsysProcessCleanup(cp, 1);
      return;
      }
    }
  else if(cp->PipeSharedSTDIN)
    {
    /* Share this process's stdin with the child.  */
    kwsysProcessSetupSharedPipe(STD_INPUT_HANDLE, &cp->PipeChildStd[0]);
    }
  else if(cp->PipeNativeSTDIN[0])
    {
    /* Use the provided native pipe.  */
    kwsysProcessSetupPipeNative(cp->PipeNativeSTDIN[0], &cp->PipeChildStd[0]);
    }
  else
    {
    /* Explicitly give the child no stdin.  */
    cp->PipeChildStd[0] = INVALID_HANDLE_VALUE;
    }

  /* Create the output pipe for the last process.
     We always create this so the pipe thread can run even if we
     do not end up giving the write end to the child below.  */
  if(!CreatePipe(&cp->Pipe[KWSYSPE_PIPE_STDOUT].Read,
                 &cp->Pipe[KWSYSPE_PIPE_STDOUT].Write, 0, 0))
    {
    kwsysProcessCleanup(cp, 1);
    return;
    }

  if(cp->PipeFileSTDOUT)
    {
    /* Use a file for stdout.  */
    if(!kwsysProcessSetupOutputPipeFile(&cp->PipeChildStd[1],
                                        cp->PipeFileSTDOUT))
      {
      kwsysProcessCleanup(cp, 1);
      return;
      }
    }
  else if(cp->PipeSharedSTDOUT)
    {
    /* Use the parent stdout.  */
    kwsysProcessSetupSharedPipe(STD_OUTPUT_HANDLE, &cp->PipeChildStd[1]);
    }
  else if(cp->PipeNativeSTDOUT[1])
    {
    /* Use the given handle for stdout.  */
    kwsysProcessSetupPipeNative(cp->PipeNativeSTDOUT[1], &cp->PipeChildStd[1]);
    }
  else
    {
    /* Use our pipe for stdout.  Duplicate the handle since our waker
       thread will use the original.  Do not make it inherited yet.  */
    if(!DuplicateHandle(GetCurrentProcess(),
                        cp->Pipe[KWSYSPE_PIPE_STDOUT].Write,
                        GetCurrentProcess(), &cp->PipeChildStd[1],
                        0, FALSE, DUPLICATE_SAME_ACCESS))
      {
      kwsysProcessCleanup(cp, 1);
      return;
      }
    }

  /* Create stderr pipe to be shared by all processes in the pipeline.
     We always create this so the pipe thread can run even if we do not
     end up giving the write end to the child below.  */
  if(!CreatePipe(&cp->Pipe[KWSYSPE_PIPE_STDERR].Read,
                 &cp->Pipe[KWSYSPE_PIPE_STDERR].Write, 0, 0))
    {
    kwsysProcessCleanup(cp, 1);
    return;
    }

  if(cp->PipeFileSTDERR)
    {
    /* Use a file for stderr.  */
    if(!kwsysProcessSetupOutputPipeFile(&cp->PipeChildStd[2],
                                        cp->PipeFileSTDERR))
      {
      kwsysProcessCleanup(cp, 1);
      return;
      }
    }
  else if(cp->PipeSharedSTDERR)
    {
    /* Use the parent stderr.  */
    kwsysProcessSetupSharedPipe(STD_ERROR_HANDLE, &cp->PipeChildStd[2]);
    }
  else if(cp->PipeNativeSTDERR[1])
    {
    /* Use the given handle for stderr.  */
    kwsysProcessSetupPipeNative(cp->PipeNativeSTDERR[1], &cp->PipeChildStd[2]);
    }
  else
    {
    /* Use our pipe for stderr.  Duplicate the handle since our waker
       thread will use the original.  Do not make it inherited yet.  */
    if(!DuplicateHandle(GetCurrentProcess(),
                        cp->Pipe[KWSYSPE_PIPE_STDERR].Write,
                        GetCurrentProcess(), &cp->PipeChildStd[2],
                        0, FALSE, DUPLICATE_SAME_ACCESS))
      {
      kwsysProcessCleanup(cp, 1);
      return;
      }
    }

  /* Create the pipeline of processes.  */
  {
  /* Child startup control data.  */
  kwsysProcessCreateInformation si;
  HANDLE nextStdInput = cp->PipeChildStd[0];

  /* Initialize startup info data.  */
  ZeroMemory(&si, sizeof(si));
  si.StartupInfo.cb = sizeof(si.StartupInfo);

  /* Decide whether a child window should be shown.  */
  si.StartupInfo.dwFlags |= STARTF_USESHOWWINDOW;
  si.StartupInfo.wShowWindow =
    (unsigned short)(cp->HideWindow?SW_HIDE:SW_SHOWDEFAULT);

  /* Connect the child's output pipes to the threads.  */
  si.StartupInfo.dwFlags |= STARTF_USESTDHANDLES;

  for(i=0; i < cp->NumberOfCommands; ++i)
    {
    /* Setup the process's pipes.  */
    si.hStdInput = nextStdInput;
    if (i == cp->NumberOfCommands-1)
      {
      /* The last child gets the overall stdout.  */
      nextStdInput = INVALID_HANDLE_VALUE;
      si.hStdOutput = cp->PipeChildStd[1];
      }
    else
      {
      /* Create a pipe to sit between the children.  */
      HANDLE p[2] = {INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE};
      if (!CreatePipe(&p[0], &p[1], 0, 0))
        {
        if (nextStdInput != cp->PipeChildStd[0])
          {
          kwsysProcessCleanupHandle(&nextStdInput);
          }
        kwsysProcessCleanup(cp, 1);
        return;
        }
      nextStdInput = p[0];
      si.hStdOutput = p[1];
      }
    si.hStdError = cp->MergeOutput? cp->PipeChildStd[1] : cp->PipeChildStd[2];

    {
    int res = kwsysProcessCreate(cp, i, &si);

    /* Close our copies of pipes used between children.  */
    if (si.hStdInput != cp->PipeChildStd[0])
      {
      kwsysProcessCleanupHandle(&si.hStdInput);
      }
    if (si.hStdOutput != cp->PipeChildStd[1])
      {
      kwsysProcessCleanupHandle(&si.hStdOutput);
      }
    if (si.hStdError != cp->PipeChildStd[2] && !cp->MergeOutput)
      {
      kwsysProcessCleanupHandle(&si.hStdError);
      }
    if (res)
      {
      cp->ProcessEvents[i+1] = cp->ProcessInformation[i].hProcess;
      }
    else
      {
      if (nextStdInput != cp->PipeChildStd[0])
        {
        kwsysProcessCleanupHandle(&nextStdInput);
        }
      kwsysProcessCleanup(cp, 1);
      return;
      }
    }
    }
  }

  /* The parent process does not need the child's pipe ends.  */
  for (i=0; i < 3; ++i)
    {
    kwsysProcessCleanupHandle(&cp->PipeChildStd[i]);
    }

  /* Restore the working directory.  */
  if(cp->RealWorkingDirectory)
    {
    SetCurrentDirectoryW(cp->RealWorkingDirectory);
    free(cp->RealWorkingDirectory);
    cp->RealWorkingDirectory = 0;
    }

  /* The timeout period starts now.  */
  cp->StartTime = kwsysProcessTimeGetCurrent();
  cp->TimeoutTime = kwsysProcessTimeFromDouble(-1);

  /* All processes in the pipeline have been started in suspended
     mode.  Resume them all now.  */
  for(i=0; i < cp->NumberOfCommands; ++i)
    {
    ResumeThread(cp->ProcessInformation[i].hThread);
    }

  /* ---- It is no longer safe to call kwsysProcessCleanup. ----- */
  /* Tell the pipe threads that a process has started.  */
  for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
    {
    ReleaseSemaphore(cp->Pipe[i].Reader.Ready, 1, 0);
    ReleaseSemaphore(cp->Pipe[i].Waker.Ready, 1, 0);
    }

  /* We don't care about the children's main threads.  */
  for(i=0; i < cp->NumberOfCommands; ++i)
    {
    kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hThread);
    }

  /* No pipe has reported data.  */
  cp->CurrentIndex = KWSYSPE_PIPE_COUNT;
  cp->PipesLeft = KWSYSPE_PIPE_COUNT;

  /* The process has now started.  */
  cp->State = kwsysProcess_State_Executing;
  cp->Detached = cp->OptionDetach;
}

/*--------------------------------------------------------------------------*/
void kwsysProcess_Disown(kwsysProcess* cp)
{
  int i;

  /* Make sure we are executing a detached process.  */
  if(!cp || !cp->Detached || cp->State != kwsysProcess_State_Executing ||
     cp->TimeoutExpired || cp->Killed || cp->Terminated)
    {
    return;
    }

  /* Disable the reading threads.  */
  kwsysProcessDisablePipeThreads(cp);

  /* Wait for all pipe threads to reset.  */
  for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
    {
    WaitForSingleObject(cp->Pipe[i].Reader.Reset, INFINITE);
    WaitForSingleObject(cp->Pipe[i].Waker.Reset, INFINITE);
    }

  /* We will not wait for exit, so cleanup now.  */
  kwsysProcessCleanup(cp, 0);

  /* The process has been disowned.  */
  cp->State = kwsysProcess_State_Disowned;
}

/*--------------------------------------------------------------------------*/

int kwsysProcess_WaitForData(kwsysProcess* cp, char** data, int* length,
                             double* userTimeout)
{
  kwsysProcessTime userStartTime;
  kwsysProcessTime timeoutLength;
  kwsysProcessTime timeoutTime;
  DWORD timeout;
  int user;
  int done = 0;
  int expired = 0;
  int pipeId = kwsysProcess_Pipe_None;
  DWORD w;

  /* Make sure we are executing a process.  */
  if(!cp || cp->State != kwsysProcess_State_Executing || cp->Killed ||
     cp->TimeoutExpired)
    {
    return kwsysProcess_Pipe_None;
    }

  /* Record the time at which user timeout period starts.  */
  userStartTime = kwsysProcessTimeGetCurrent();

  /* Calculate the time at which a timeout will expire, and whether it
     is the user or process timeout.  */
  user = kwsysProcessGetTimeoutTime(cp, userTimeout, &timeoutTime);

  /* Loop until we have a reason to return.  */
  while(!done && cp->PipesLeft > 0)
    {
    /* If we previously got data from a thread, let it know we are
       done with the data.  */
    if(cp->CurrentIndex < KWSYSPE_PIPE_COUNT)
      {
      KWSYSPE_DEBUG((stderr, "releasing reader %d\n", cp->CurrentIndex));
      ReleaseSemaphore(cp->Pipe[cp->CurrentIndex].Reader.Go, 1, 0);
      cp->CurrentIndex = KWSYSPE_PIPE_COUNT;
      }

    /* Setup a timeout if required.  */
    if(kwsysProcessGetTimeoutLeft(&timeoutTime, user?userTimeout:0,
                                  &timeoutLength))
      {
      /* Timeout has already expired.  */
      expired = 1;
      break;
      }
    if(timeoutTime.QuadPart < 0)
      {
      timeout = INFINITE;
      }
    else
      {
      timeout = kwsysProcessTimeToDWORD(timeoutLength);
      }

    /* Wait for a pipe's thread to signal or a process to terminate.  */
    w = WaitForMultipleObjects(cp->ProcessEventsLength, cp->ProcessEvents,
                               0, timeout);
    if(w == WAIT_TIMEOUT)
      {
      /* Timeout has expired.  */
      expired = 1;
      done = 1;
      }
    else if(w == WAIT_OBJECT_0)
      {
      /* Save the index of the reporting thread and release the mutex.
         The thread will block until we signal its Empty mutex.  */
      cp->CurrentIndex = cp->SharedIndex;
      ReleaseSemaphore(cp->SharedIndexMutex, 1, 0);

      /* Data are available or a pipe closed.  */
      if(cp->Pipe[cp->CurrentIndex].Closed)
        {
        /* The pipe closed at the write end.  Close the read end and
           inform the wakeup thread it is done with this process.  */
        kwsysProcessCleanupHandle(&cp->Pipe[cp->CurrentIndex].Read);
        ReleaseSemaphore(cp->Pipe[cp->CurrentIndex].Waker.Go, 1, 0);
        KWSYSPE_DEBUG((stderr, "wakeup %d\n", cp->CurrentIndex));
        --cp->PipesLeft;
        }
      else if(data && length)
        {
        /* Report this data.  */
        *data = cp->Pipe[cp->CurrentIndex].DataBuffer;
        *length = cp->Pipe[cp->CurrentIndex].DataLength;
        switch(cp->CurrentIndex)
          {
          case KWSYSPE_PIPE_STDOUT:
            pipeId = kwsysProcess_Pipe_STDOUT; break;
          case KWSYSPE_PIPE_STDERR:
            pipeId = kwsysProcess_Pipe_STDERR; break;
          }
        done = 1;
        }
      }
    else
      {
      /* A process has terminated.  */
      kwsysProcessDestroy(cp, w-WAIT_OBJECT_0);
      }
    }

  /* Update the user timeout.  */
  if(userTimeout)
    {
    kwsysProcessTime userEndTime = kwsysProcessTimeGetCurrent();
    kwsysProcessTime difference = kwsysProcessTimeSubtract(userEndTime,
                                                           userStartTime);
    double d = kwsysProcessTimeToDouble(difference);
    *userTimeout -= d;
    if(*userTimeout < 0)
      {
      *userTimeout = 0;
      }
    }

  /* Check what happened.  */
  if(pipeId)
    {
    /* Data are ready on a pipe.  */
    return pipeId;
    }
  else if(expired)
    {
    /* A timeout has expired.  */
    if(user)
      {
      /* The user timeout has expired.  It has no time left.  */
      return kwsysProcess_Pipe_Timeout;
      }
    else
      {
      /* The process timeout has expired.  Kill the child now.  */
      KWSYSPE_DEBUG((stderr, "killing child because timeout expired\n"));
      kwsysProcess_Kill(cp);
      cp->TimeoutExpired = 1;
      cp->Killed = 0;
      return kwsysProcess_Pipe_None;
      }
    }
  else
    {
    /* The children have terminated and no more data are available.  */
    return kwsysProcess_Pipe_None;
    }
}

/*--------------------------------------------------------------------------*/
int kwsysProcess_WaitForExit(kwsysProcess* cp, double* userTimeout)
{
  int i;
  int pipe;

  /* Make sure we are executing a process.  */
  if(!cp || cp->State != kwsysProcess_State_Executing)
    {
    return 1;
    }

  /* Wait for the process to terminate.  Ignore all data.  */
  while((pipe = kwsysProcess_WaitForData(cp, 0, 0, userTimeout)) > 0)
    {
    if(pipe == kwsysProcess_Pipe_Timeout)
      {
      /* The user timeout has expired.  */
      return 0;
      }
    }

  KWSYSPE_DEBUG((stderr, "no more data\n"));

  /* When the last pipe closes in WaitForData, the loop terminates
     without releasing the pipe's thread.  Release it now.  */
  if(cp->CurrentIndex < KWSYSPE_PIPE_COUNT)
    {
    KWSYSPE_DEBUG((stderr, "releasing reader %d\n", cp->CurrentIndex));
    ReleaseSemaphore(cp->Pipe[cp->CurrentIndex].Reader.Go, 1, 0);
    cp->CurrentIndex = KWSYSPE_PIPE_COUNT;
    }

  /* Wait for all pipe threads to reset.  */
  for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
    {
    KWSYSPE_DEBUG((stderr, "waiting reader reset %d\n", i));
    WaitForSingleObject(cp->Pipe[i].Reader.Reset, INFINITE);
    KWSYSPE_DEBUG((stderr, "waiting waker reset %d\n", i));
    WaitForSingleObject(cp->Pipe[i].Waker.Reset, INFINITE);
    }

  /* ---- It is now safe again to call kwsysProcessCleanup. ----- */
  /* Close all the pipes.  */
  kwsysProcessCleanup(cp, 0);

  /* Determine the outcome.  */
  if(cp->Killed)
    {
    /* We killed the child.  */
    cp->State = kwsysProcess_State_Killed;
    }
  else if(cp->TimeoutExpired)
    {
    /* The timeout expired.  */
    cp->State = kwsysProcess_State_Expired;
    }
  else
    {
    /* The children exited.  Report the outcome of the last process.  */
    cp->ExitCode = cp->CommandExitCodes[cp->NumberOfCommands-1];
    if((cp->ExitCode & 0xF0000000) == 0xC0000000)
      {
      /* Child terminated due to exceptional behavior.  */
      cp->State = kwsysProcess_State_Exception;
      cp->ExitValue = 1;
      kwsysProcessSetExitException(cp, cp->ExitCode);
      }
    else
      {
      /* Child exited without exception.  */
      cp->State = kwsysProcess_State_Exited;
      cp->ExitException = kwsysProcess_Exception_None;
      cp->ExitValue = cp->ExitCode;
      }
    }

  return 1;
}

/*--------------------------------------------------------------------------*/
void kwsysProcess_Kill(kwsysProcess* cp)
{
  int i;
  /* Make sure we are executing a process.  */
  if(!cp || cp->State != kwsysProcess_State_Executing || cp->TimeoutExpired ||
     cp->Killed)
    {
    KWSYSPE_DEBUG((stderr, "kill: child not executing\n"));
    return;
    }

  /* Disable the reading threads.  */
  KWSYSPE_DEBUG((stderr, "kill: disabling pipe threads\n"));
  kwsysProcessDisablePipeThreads(cp);

  /* Skip actually killing the child if it has already terminated.  */
  if(cp->Terminated)
    {
    KWSYSPE_DEBUG((stderr, "kill: child already terminated\n"));
    return;
    }

  /* Kill the children.  */
  cp->Killed = 1;
  for(i=0; i < cp->NumberOfCommands; ++i)
    {
    kwsysProcessKillTree(cp->ProcessInformation[i].dwProcessId);
    // close the handle if we kill it
    kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hThread);
    kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hProcess);
    }

  /* We are killing the children and ignoring all data.  Do not wait
     for them to exit.  */
}

/*--------------------------------------------------------------------------*/

/*
  Function executed for each pipe's thread.  Argument is a pointer to
  the kwsysProcessPipeData instance for this thread.
*/
DWORD WINAPI kwsysProcessPipeThreadRead(LPVOID ptd)
{
  kwsysProcessPipeData* td = (kwsysProcessPipeData*)ptd;
  kwsysProcess* cp = td->Process;

  /* Wait for a process to be ready.  */
  while((WaitForSingleObject(td->Reader.Ready, INFINITE), !cp->Deleting))
    {
    /* Read output from the process for this thread's pipe.  */
    kwsysProcessPipeThreadReadPipe(cp, td);

    /* Signal the main thread we have reset for a new process.  */
    ReleaseSemaphore(td->Reader.Reset, 1, 0);
    }
  return 0;
}

/*--------------------------------------------------------------------------*/

/*
  Function called in each pipe's thread to handle data for one
  execution of a subprocess.
*/
void kwsysProcessPipeThreadReadPipe(kwsysProcess* cp, kwsysProcessPipeData* td)
{
  /* Wait for space in the thread's buffer. */
  while((KWSYSPE_DEBUG((stderr, "wait for read %d\n", td->Index)),
         WaitForSingleObject(td->Reader.Go, INFINITE), !td->Closed))
    {
    KWSYSPE_DEBUG((stderr, "reading %d\n", td->Index));

    /* Read data from the pipe.  This may block until data are available.  */
    if(!ReadFile(td->Read, td->DataBuffer, KWSYSPE_PIPE_BUFFER_SIZE,
                 &td->DataLength, 0))
      {
      if(GetLastError() != ERROR_BROKEN_PIPE)
        {
        /* UNEXPECTED failure to read the pipe.  */
        }

      /* The pipe closed.  There are no more data to read.  */
      td->Closed = 1;
      KWSYSPE_DEBUG((stderr, "read closed %d\n", td->Index));
      }

    KWSYSPE_DEBUG((stderr, "read %d\n", td->Index));

    /* Wait for our turn to be handled by the main thread.  */
    WaitForSingleObject(cp->SharedIndexMutex, INFINITE);

    KWSYSPE_DEBUG((stderr, "reporting read %d\n", td->Index));

    /* Tell the main thread we have something to report.  */
    cp->SharedIndex = td->Index;
    ReleaseSemaphore(cp->Full, 1, 0);
    }

  /* We were signalled to exit with our buffer empty.  Reset the
     mutex for a new process.  */
  KWSYSPE_DEBUG((stderr, "self releasing reader %d\n", td->Index));
  ReleaseSemaphore(td->Reader.Go, 1, 0);
}

/*--------------------------------------------------------------------------*/

/*
  Function executed for each pipe's thread.  Argument is a pointer to
  the kwsysProcessPipeData instance for this thread.
*/
DWORD WINAPI kwsysProcessPipeThreadWake(LPVOID ptd)
{
  kwsysProcessPipeData* td = (kwsysProcessPipeData*)ptd;
  kwsysProcess* cp = td->Process;

  /* Wait for a process to be ready.  */
  while((WaitForSingleObject(td->Waker.Ready, INFINITE), !cp->Deleting))
    {
    /* Wait for a possible wakeup.  */
    kwsysProcessPipeThreadWakePipe(cp, td);

    /* Signal the main thread we have reset for a new process.  */
    ReleaseSemaphore(td->Waker.Reset, 1, 0);
    }
  return 0;
}

/*--------------------------------------------------------------------------*/

/*
  Function called in each pipe's thread to handle reading thread
  wakeup for one execution of a subprocess.
*/
void kwsysProcessPipeThreadWakePipe(kwsysProcess* cp, kwsysProcessPipeData* td)
{
  (void)cp;

  /* Wait for a possible wake command. */
  KWSYSPE_DEBUG((stderr, "wait for wake %d\n", td->Index));
  WaitForSingleObject(td->Waker.Go, INFINITE);
  KWSYSPE_DEBUG((stderr, "waking %d\n", td->Index));

  /* If the pipe is not closed, we need to wake up the reading thread.  */
  if(!td->Closed)
    {
    DWORD dummy;
    KWSYSPE_DEBUG((stderr, "waker %d writing byte\n", td->Index));
    WriteFile(td->Write, "", 1, &dummy, 0);
    KWSYSPE_DEBUG((stderr, "waker %d wrote byte\n", td->Index));
    }
}

/*--------------------------------------------------------------------------*/
/* Initialize a process control structure for kwsysProcess_Execute.  */
int kwsysProcessInitialize(kwsysProcess* cp)
{
  /* Reset internal status flags.  */
  cp->TimeoutExpired = 0;
  cp->Terminated = 0;
  cp->Killed = 0;
  cp->ExitException = kwsysProcess_Exception_None;
  cp->ExitCode = 1;
  cp->ExitValue = 1;

  /* Reset error data.  */
  cp->ErrorMessage[0] = 0;
  strcpy(cp->ExitExceptionString, "No exception");

  /* Allocate process information for each process.  */
  cp->ProcessInformation =
    (PROCESS_INFORMATION*)malloc(sizeof(PROCESS_INFORMATION) *
                                 cp->NumberOfCommands);
  if(!cp->ProcessInformation)
    {
    return 0;
    }
  ZeroMemory(cp->ProcessInformation,
             sizeof(PROCESS_INFORMATION) * cp->NumberOfCommands);
  if(cp->CommandExitCodes)
    {
    free(cp->CommandExitCodes);
    }
  cp->CommandExitCodes = (DWORD*)malloc(sizeof(DWORD)*cp->NumberOfCommands);
  if(!cp->CommandExitCodes)
    {
    return 0;
    }
  ZeroMemory(cp->CommandExitCodes, sizeof(DWORD)*cp->NumberOfCommands);

  /* Allocate event wait array.  The first event is cp->Full, the rest
     are the process termination events.  */
  cp->ProcessEvents = (PHANDLE)malloc(sizeof(HANDLE)*(cp->NumberOfCommands+1));
  if(!cp->ProcessEvents)
    {
    return 0;
    }
  ZeroMemory(cp->ProcessEvents, sizeof(HANDLE) * (cp->NumberOfCommands+1));
  cp->ProcessEvents[0] = cp->Full;
  cp->ProcessEventsLength = cp->NumberOfCommands+1;

  /* Allocate space to save the real working directory of this process.  */
  if(cp->WorkingDirectory)
    {
    cp->RealWorkingDirectoryLength = GetCurrentDirectoryW(0, 0);
    if(cp->RealWorkingDirectoryLength > 0)
      {
      cp->RealWorkingDirectory = malloc(cp->RealWorkingDirectoryLength * sizeof(wchar_t));
      if(!cp->RealWorkingDirectory)
        {
        return 0;
        }
      }
    }
  {
  int i;
  for (i=0; i < 3; ++i)
    {
    cp->PipeChildStd[i] = INVALID_HANDLE_VALUE;
    }
  }

  return 1;
}

/*--------------------------------------------------------------------------*/
static int kwsysProcessCreateChildHandle(PHANDLE out, HANDLE in, int isStdIn)
{
  DWORD flags;

  /* Check whether the handle is valid for this process.  */
  if (in != INVALID_HANDLE_VALUE && GetHandleInformation(in, &flags))
    {
    /* Use the handle as-is if it is already inherited.  */
    if (flags & HANDLE_FLAG_INHERIT)
      {
      *out = in;
      return 1;
      }

    /* Create an inherited copy of this handle.  */
    return DuplicateHandle(GetCurrentProcess(), in,
                           GetCurrentProcess(), out,
                           0, TRUE, DUPLICATE_SAME_ACCESS);
    }
  else
    {
    /* The given handle is not valid for this process.  Some child
       processes may break if they do not have a valid standard handle,
       so open NUL to give to the child.  */
    SECURITY_ATTRIBUTES sa;
    ZeroMemory(&sa, sizeof(sa));
    sa.nLength = (DWORD)sizeof(sa);
    sa.bInheritHandle = 1;
    *out = CreateFileW(L"NUL",
                       (isStdIn ? GENERIC_READ :
                        (GENERIC_WRITE | FILE_READ_ATTRIBUTES)),
                       FILE_SHARE_READ|FILE_SHARE_WRITE,
                       &sa, OPEN_EXISTING, 0, 0);
    return *out != INVALID_HANDLE_VALUE;
    }

}

/*--------------------------------------------------------------------------*/
int kwsysProcessCreate(kwsysProcess* cp, int index,
                       kwsysProcessCreateInformation* si)
{
  int res =

    /* Create inherited copies the handles.  */
    kwsysProcessCreateChildHandle(&si->StartupInfo.hStdInput,
                                  si->hStdInput, 1) &&
    kwsysProcessCreateChildHandle(&si->StartupInfo.hStdOutput,
                                  si->hStdOutput, 0) &&
    kwsysProcessCreateChildHandle(&si->StartupInfo.hStdError,
                                  si->hStdError, 0) &&

    /* Create the child in a suspended state so we can wait until all
       children have been created before running any one.  */
    CreateProcessW(0, cp->Commands[index], 0, 0, TRUE, CREATE_SUSPENDED, 0,
                   0, &si->StartupInfo, &cp->ProcessInformation[index]);

  /* Close the inherited copies of the handles. */
  if (si->StartupInfo.hStdInput != si->hStdInput)
    {
    kwsysProcessCleanupHandle(&si->StartupInfo.hStdInput);
    }
  if (si->StartupInfo.hStdOutput != si->hStdOutput)
    {
    kwsysProcessCleanupHandle(&si->StartupInfo.hStdOutput);
    }
  if (si->StartupInfo.hStdError != si->hStdError)
    {
    kwsysProcessCleanupHandle(&si->StartupInfo.hStdError);
    }

  return res;
}

/*--------------------------------------------------------------------------*/
void kwsysProcessDestroy(kwsysProcess* cp, int event)
{
  int i;
  int index;

  /* Find the process index for the termination event.  */
  for(index=0; index < cp->NumberOfCommands; ++index)
    {
    if(cp->ProcessInformation[index].hProcess == cp->ProcessEvents[event])
      {
      break;
      }
    }

  /* Check the exit code of the process.  */
  GetExitCodeProcess(cp->ProcessInformation[index].hProcess,
                     &cp->CommandExitCodes[index]);

  /* Close the process handle for the terminated process.  */
  kwsysProcessCleanupHandle(&cp->ProcessInformation[index].hProcess);

  /* Remove the process from the available events.  */
  cp->ProcessEventsLength -= 1;
  for(i=event; i < cp->ProcessEventsLength; ++i)
    {
    cp->ProcessEvents[i] = cp->ProcessEvents[i+1];
    }

  /* Check if all processes have terminated.  */
  if(cp->ProcessEventsLength == 1)
    {
    cp->Terminated = 1;

    /* Close our copies of the pipe write handles so the pipe threads
       can detect end-of-data.  */
    for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
      {
      /* TODO: If the child created its own child (our grandchild)
         which inherited a copy of the pipe write-end then the pipe
         may not close and we will still need the waker write pipe.
         However we still want to be able to detect end-of-data in the
         normal case.  The reader thread will have to switch to using
         PeekNamedPipe to read the last bit of data from the pipe
         without blocking.  This is equivalent to using a non-blocking
         read on posix.  */
      KWSYSPE_DEBUG((stderr, "closing wakeup write %d\n", i));
      kwsysProcessCleanupHandle(&cp->Pipe[i].Write);
      }
    }
}

/*--------------------------------------------------------------------------*/
int kwsysProcessSetupOutputPipeFile(PHANDLE phandle, const char* name)
{
  HANDLE fout;
  wchar_t* wname;
  if(!name)
    {
    return 1;
    }

  /* Close the existing handle.  */
  kwsysProcessCleanupHandle(phandle);

  /* Create a handle to write a file for the pipe.  */
  wname = kwsysEncoding_DupToWide(name);
  fout = CreateFileW(wname, GENERIC_WRITE, FILE_SHARE_READ, 0,
                    CREATE_ALWAYS, 0, 0);
  free(wname);
  if(fout == INVALID_HANDLE_VALUE)
    {
    return 0;
    }

  /* Assign the replacement handle.  */
  *phandle = fout;
  return 1;
}

/*--------------------------------------------------------------------------*/
void kwsysProcessSetupSharedPipe(DWORD nStdHandle, PHANDLE handle)
{
  /* Close the existing handle.  */
  kwsysProcessCleanupHandle(handle);
  /* Store the new standard handle.  */
  *handle = GetStdHandle(nStdHandle);
}

/*--------------------------------------------------------------------------*/
void kwsysProcessSetupPipeNative(HANDLE native, PHANDLE handle)
{
  /* Close the existing handle.  */
  kwsysProcessCleanupHandle(handle);
  /* Store the new given handle.  */
  *handle = native;
}

/*--------------------------------------------------------------------------*/

/* Close the given handle if it is open.  Reset its value to 0.  */
void kwsysProcessCleanupHandle(PHANDLE h)
{
  if(h && *h && *h != INVALID_HANDLE_VALUE &&
     *h != GetStdHandle(STD_INPUT_HANDLE) &&
     *h != GetStdHandle(STD_OUTPUT_HANDLE) &&
     *h != GetStdHandle(STD_ERROR_HANDLE))
    {
    CloseHandle(*h);
    *h = INVALID_HANDLE_VALUE;
    }
}

/*--------------------------------------------------------------------------*/

/* Close all handles created by kwsysProcess_Execute.  */
void kwsysProcessCleanup(kwsysProcess* cp, int error)
{
  int i;
  /* If this is an error case, report the error.  */
  if(error)
    {
    /* Construct an error message if one has not been provided already.  */
    if(cp->ErrorMessage[0] == 0)
      {
      /* Format the error message.  */
      DWORD original = GetLastError();
      wchar_t err_msg[KWSYSPE_PIPE_BUFFER_SIZE];
      DWORD length = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM |
                                   FORMAT_MESSAGE_IGNORE_INSERTS, 0, original,
                                   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                   err_msg, KWSYSPE_PIPE_BUFFER_SIZE, 0);
      WideCharToMultiByte(CP_UTF8, 0, err_msg, -1, cp->ErrorMessage,
                          KWSYSPE_PIPE_BUFFER_SIZE, NULL, NULL);
      if(length < 1)
        {
        /* FormatMessage failed.  Use a default message.  */
        _snprintf(cp->ErrorMessage, KWSYSPE_PIPE_BUFFER_SIZE,
                  "Process execution failed with error 0x%X.  "
                  "FormatMessage failed with error 0x%X",
                  original, GetLastError());
        }
      }

    /* Remove trailing period and newline, if any.  */
    kwsysProcessCleanErrorMessage(cp);

    /* Set the error state.  */
    cp->State = kwsysProcess_State_Error;

    /* Cleanup any processes already started in a suspended state.  */
    if(cp->ProcessInformation)
      {
      for(i=0; i < cp->NumberOfCommands; ++i)
        {
        if(cp->ProcessInformation[i].hProcess)
          {
          TerminateProcess(cp->ProcessInformation[i].hProcess, 255);
          WaitForSingleObject(cp->ProcessInformation[i].hProcess, INFINITE);
          }
        }
      for(i=0; i < cp->NumberOfCommands; ++i)
        {
