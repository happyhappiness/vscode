bool WindowsRunCommand(const char* command, const char* dir, 
                       std::string& output, int& retVal, bool verbose) 
{
  //verbose = true;
  std::cerr << std::endl 
	    << "WindowsRunCommand(" << command << ")" << std::endl 
	    << std::flush;
  const int BUFFER_SIZE = 4096;
  char buf[BUFFER_SIZE];
 
//i/o buffer 
  STARTUPINFO si;
  SECURITY_ATTRIBUTES sa;
  SECURITY_DESCRIPTOR sd;
 
//security information for pipes 
  PROCESS_INFORMATION pi;
  HANDLE newstdin,newstdout,read_stdout,write_stdin;
 
//pipe handles 
  if (IsWinNT()) 
//initialize security descriptor (Windows NT) 
    {
    InitializeSecurityDescriptor(&sd,SECURITY_DESCRIPTOR_REVISION);
    SetSecurityDescriptorDacl(&sd, true, NULL, false);
    sa.lpSecurityDescriptor = &sd;
 
    }
  else sa.lpSecurityDescriptor = NULL;

  sa.nLength = sizeof(SECURITY_ATTRIBUTES);
  sa.bInheritHandle = true;
 
//allow inheritable handles 
  if (!CreatePipe(&newstdin,&write_stdin,&sa,0)) 
//create stdin pipe 
    {
    std::cerr << "CreatePipe" << std::endl;
    return false;
 
    }
  if (!CreatePipe(&read_stdout,&newstdout,&sa,0)) 
//create stdout pipe 
    {
    std::cerr << "CreatePipe" << std::endl;
    CloseHandle(newstdin);
    CloseHandle(write_stdin);
    return false;
 
    }
  GetStartupInfo(&si);
 
//set startupinfo for the spawned process 
  /* The dwFlags member tells CreateProcess how to make the
   * process. STARTF_USESTDHANDLES validates the hStd*
   * members. STARTF_USESHOWWINDOW validates the wShowWindow
   * member. */ 
  
  si.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
  si.wShowWindow = SW_HIDE;
  si.hStdOutput = newstdout;
  si.hStdError = newstdout;
 
//set the new handles for the child process si.hStdInput = newstdin;
  char* commandAndArgs = strcpy(new char[strlen(command)+1], command);
  if (!CreateProcess(NULL,commandAndArgs,NULL,NULL,TRUE,CREATE_NEW_CONSOLE, 
                     NULL,dir,&si,&pi)) 
    {
    std::cerr << "CreateProcess failed " << commandAndArgs << std::endl;
    CloseHandle(newstdin);
    CloseHandle(newstdout);
    CloseHandle(read_stdout);
    CloseHandle(write_stdin);
    delete [] commandAndArgs;
    return false;
 
    }
  delete [] commandAndArgs;
  unsigned long exit=0;
 
//process exit code unsigned 
  unsigned long bread;
 
//bytes read unsigned 
  unsigned long avail;
 
//bytes available 
  memset(buf, 0, sizeof(buf));
  for(;;) 
//main program loop 
    {
    Sleep(10);
    //std::cout << "Check for process..." << std::endl;
    GetExitCodeProcess(pi.hProcess,&exit);
 
//while the process is running 
    if (exit != STILL_ACTIVE) break;
 
//check to see if there is any data to read from stdout 
    //std::cout << "Peek for data..." << std::endl;
    PeekNamedPipe(read_stdout,buf,1023,&bread,&avail,NULL);
    if (bread != 0) 
      {
      memset(buf, 0, sizeof(buf));
      if (avail > 1023) 
        {
        while (bread >= 1023) 
          {
	  //std::cout << "Read data..." << std::endl;
          ReadFile(read_stdout,buf,1023,&bread,NULL);
 
//read the stdout pipe 
          printf("%s",buf);
          memset(buf, 0, sizeof(buf));
 
          }
 
        }
      else 
        {
        ReadFile(read_stdout,buf,1023,&bread,NULL);
        output += buf;
        output += "\n";
        if(verbose) 
          {
          std::cerr << verbose << " [{" << buf << "}]" 
		    << std::endl << std::flush;
 
          }
 
        }
 
      }
 
    }
  CloseHandle(pi.hThread);
  CloseHandle(pi.hProcess);
  CloseHandle(newstdin);
 
//clean stuff up 
  CloseHandle(newstdout);
  CloseHandle(read_stdout);
  CloseHandle(write_stdin);
  retVal = exit;
  std::cerr << std::endl << "End of WindowsRunCommand(" << command << ")" << std::endl << std::flush;
  return true;
 
}