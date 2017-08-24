@@ -974,133 +974,7 @@ bool cmSystemTools::RunCommand(const char* command,
   return cmSystemTools::RunCommand(command, output, foo, dir, verbose);
 }
 
-
 #if defined(WIN32) && !defined(__CYGWIN__)
-// Code from a Borland web site with the following explaination :
-/* In this article, I will explain how to spawn a console application and redirect its standard input/output using anonymous pipes. An anonymous pipe is a pipe that goes only in one direction (read pipe, write pipe, etc.). Maybe you are asking, "why would I ever need to do this sort of thing?" One example would be a Windows telnet server, where you spawn a shell and listen on a port and send and receive data between the shell and the socket client. (Windows does not really have a built-in remote shell). 
-First, we should talk about pipes. A pipe in Windows is simply a method of communication, often between process. The SDK defines a pipe as "a communication conduit with two ends; a process with a handle to one end can communicate with a process having a handle to the other end." In our case, we are using "anonymous" pipes, one-way pipes that "transfer data between a parent process and a child process or between two child processes of the same parent process." It's easiest to imagine a pipe as its namesake. An actual pipe running between processes that can carry data. 
-
-We are using anonymous pipes because the console app we are spawning is a child process. We use the CreatePipe function which will create an anonymous pipe and return a read handle and a write handle. We will create two pipes, on for stdin and one for stdout. We will then monitor the read end of the stdout pipe to check for display on our child process. Every time there is something availabe for reading, we will display it in our app. Consequently, we check for input in our app and send it off to the write end of the stdin pipe. 
-*/
-
-inline bool IsWinNT()  //check if we're running NT
-{
-  OSVERSIONINFO osv;
-  osv.dwOSVersionInfoSize = sizeof(osv);
-  GetVersionEx(&osv);
-  return (osv.dwPlatformId == VER_PLATFORM_WIN32_NT);
-}
-
-//---------------------------------------------------------------------------
-bool WindowsRunCommand(const char* command,
-                       const char* dir,
-                       std::string& output,
-                       int& retVal,
-                       bool verbose)
-{
-  const int BUFFER_SIZE = 4096;
-  char buf[BUFFER_SIZE];                //i/o buffer
-  
-  STARTUPINFO si;
-  SECURITY_ATTRIBUTES sa;
-  SECURITY_DESCRIPTOR sd;        //security information for pipes
-  PROCESS_INFORMATION pi;
-  HANDLE newstdin,newstdout,read_stdout,write_stdin; //pipe handles
-
-  if (IsWinNT())                 //initialize security descriptor (Windows NT)
-    {
-    InitializeSecurityDescriptor(&sd,SECURITY_DESCRIPTOR_REVISION);
-    SetSecurityDescriptorDacl(&sd, true, NULL, false);
-    sa.lpSecurityDescriptor = &sd;
-    }
-  else sa.lpSecurityDescriptor = NULL;
-  sa.nLength = sizeof(SECURITY_ATTRIBUTES);
-  sa.bInheritHandle = true;      //allow inheritable handles
-
-  if (!CreatePipe(&newstdin,&write_stdin,&sa,0)) //create stdin pipe
-    {
-    cmSystemTools::Error("CreatePipe");
-    return false;
-    }
-  if (!CreatePipe(&read_stdout,&newstdout,&sa,0)) //create stdout pipe
-    {
-    cmSystemTools::Error("CreatePipe");
-    CloseHandle(newstdin);
-    CloseHandle(write_stdin);
-    return false;
-    }
-
-  GetStartupInfo(&si);           //set startupinfo for the spawned process
-                                /*
-                                  The dwFlags member tells CreateProcess how to make the process.
-                                  STARTF_USESTDHANDLES validates the hStd* members. STARTF_USESHOWWINDOW
-                                  validates the wShowWindow member.
-                                */
-  si.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
-  si.wShowWindow = SW_HIDE;
-  si.hStdOutput = newstdout;
-  si.hStdError = newstdout;      //set the new handles for the child process
-  si.hStdInput = newstdin;
-  char* commandAndArgs = strcpy(new char[strlen(command)+1], command);
-  if (!CreateProcess(NULL,commandAndArgs,NULL,NULL,TRUE,CREATE_NEW_CONSOLE,
-                     NULL,dir,&si,&pi))
-    {
-    cmSystemTools::Error("CreateProcess failed", commandAndArgs);
-    CloseHandle(newstdin);
-    CloseHandle(newstdout);
-    CloseHandle(read_stdout);
-    CloseHandle(write_stdin);
-    delete [] commandAndArgs;
-    return false;
-    }
-  delete [] commandAndArgs;
-
-  unsigned long exit=0;          //process exit code
-  unsigned long bread;           //bytes read
-  unsigned long avail;           //bytes available
-
-  memset(buf, 0, sizeof(buf));
-  for(;;)                        //main program loop
-    {
-    GetExitCodeProcess(pi.hProcess,&exit); //while the process is running
-    if (exit != STILL_ACTIVE)
-      break;
-    //check to see if there is any data to read from stdout
-    PeekNamedPipe(read_stdout,buf,1023,&bread,&avail,NULL);
-    if (bread != 0)
-      {
-      memset(buf, 0, sizeof(buf));
-      if (avail > 1023)
-        {
-        while (bread >= 1023)
-          {
-          ReadFile(read_stdout,buf,1023,&bread,NULL); //read the stdout pipe
-          printf("%s",buf);
-          memset(buf, 0, sizeof(buf));
-          }
-        }
-      else
-        {
-        ReadFile(read_stdout,buf,1023,&bread,NULL);
-        output += buf;
-        output += "\n";
-        if(verbose)
-          {
-          std::cout << buf << "\n" << std::flush;
-          }
-        }
-      }
-    }
-  CloseHandle(pi.hThread);
-  CloseHandle(pi.hProcess);
-  CloseHandle(newstdin);         //clean stuff up
-  CloseHandle(newstdout);
-  CloseHandle(read_stdout);
-  CloseHandle(write_stdin);
-  retVal = exit;
-  return true;
-}
-
 // use this for shell commands like echo and dir
 bool RunCommandViaSystem(const char* command,
                          const char* dir,
@@ -1161,7 +1035,7 @@ bool RunCommandViaSystem(const char* command,
 
 
 // run a command unix uses popen (easy)
-// windows uses CreateProcess (difficult) or system for built in commands
+// windows uses system and ShortPath
 bool cmSystemTools::RunCommand(const char* command, 
                                std::string& output,
                                int &retVal, 
@@ -1178,21 +1052,61 @@ bool cmSystemTools::RunCommand(const char* command,
   // try to find the program, and if the program can not be
   // found use system to run the command as it must be a built in
   // shell command like echo or dir
-  if(command[0] != '\"')
+  int count = 0;
+  if(command[0] == '\"')
     {
-    cmRegularExpression nonQuoted("^([^ \t]*)[ \t](.*)");
-    if(nonQuoted.find(command))
+    // count the number of quotes
+    for(const char* s = command; *s != 0; ++s)
       {
-      std::string cmd = nonQuoted.match(1);
-      if(cmSystemTools::FindProgram(cmd.c_str()) == "")
+      if(*s == '\"')
+        {
+        count++;
+        if(count > 2)
+          {
+          break;
+          }
+        }      
+      }
+    // if there are more than two double quotes use 
+    // GetShortPathName, the cmd.exe program in windows which
+    // is used by system fails to execute if there are more than
+    // one set of quotes in the arguments
+    if(count > 2)
+      {
+      cmRegularExpression quoted("^\"([^\"]*)\"[ \t](.*)");
+      if(quoted.find(command))
+        {
+        std::string shortCmd;
+        std::string cmd = quoted.match(1);
+        std::string args = quoted.match(2);
+        char *buffer = new char[cmd.size()+1];
+        if(GetShortPathName(cmd.c_str(), buffer, 
+                            int(cmd.size())) != 0)
+          {
+          shortCmd = buffer;
+          shortCmd += " ";
+          shortCmd += args;
+          }
+        else
+          {
+          cmSystemTools::Error("Could not get GetShortPathName for ", 
+                               cmd.c_str());
+          return false;
+          }
+        return RunCommandViaSystem(shortCmd.c_str(), dir, 
+                                   output, retVal, verbose);
+        }
+      else
         {
-        return RunCommandViaSystem(command, dir, output, retVal, verbose);
+        cmSystemTools::Error("Could not parse command line with quotes ", 
+                             command);
         }
       }
     }
-  // best case is the command is an executable and we run it this way
-  return WindowsRunCommand(command, dir, output, retVal, verbose);
+  // if there is only one set of quotes or no quotes then just run the command
+  return RunCommandViaSystem(command, dir, output, retVal, verbose);
 #else
+  // if only popen worked on windows.....
   std::string commandInDir;
   if(dir)
     {