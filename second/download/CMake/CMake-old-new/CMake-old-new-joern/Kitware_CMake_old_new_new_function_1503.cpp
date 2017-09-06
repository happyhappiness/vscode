static BOOL RealPopenCreateProcess(const char *cmdstring,
                                   const char *path, 
                                   const char *szConsoleSpawn,
                                   HANDLE hStdin,
                                   HANDLE hStdout,
                                   HANDLE hStderr,
                                   HANDLE *hProcess)
{
  PROCESS_INFORMATION piProcInfo;
  STARTUPINFO siStartInfo;
  char *s1,*s2, *s3 = " /c ";
  int i;
  int x;
  if (i = GetEnvironmentVariable("COMSPEC",NULL,0)) 
    {
    char *comshell;

    s1 = (char *)_alloca(i);
    if (!(x = GetEnvironmentVariable("COMSPEC", s1, i)))
      {
      return x;
      }

    /* Explicitly check if we are using COMMAND.COM.  If we are
     * then use the w9xpopen hack.
     */
    comshell = s1 + x;
    while (comshell >= s1 && *comshell != '\\')
      --comshell;
    ++comshell;

    if (GetVersion() < 0x80000000 &&
        STRICMP(comshell, "command.com") != 0) 
      {
      /* NT/2000 and not using command.com. */
      x = i + (int)strlen(s3) + (int)strlen(cmdstring) + 1;
      s2 = (char *)_alloca(x);
      ZeroMemory(s2, x);
      //sprintf(s2, "%s%s%s", s1, s3, cmdstring);
      sprintf(s2, "%s", cmdstring);
      }
    else 
      {
      /*
       * Oh gag, we're on Win9x or using COMMAND.COM. Use
       * the workaround listed in KB: Q150956
       */
      char modulepath[_MAX_PATH];
      struct stat statinfo;
      GetModuleFileName(NULL, modulepath, sizeof(modulepath));
      for (i = x = 0; modulepath[i]; i++)
        if (modulepath[i] == '\\')
          x = i+1;
      modulepath[x] = '\0';
      /* Create the full-name to w9xpopen, so we can test it exists */
      strncat(modulepath, 
              szConsoleSpawn, 
              (sizeof(modulepath)/sizeof(modulepath[0]))
              -strlen(modulepath));
      if (stat(modulepath, &statinfo) != 0) 
        {
          /* Eeek - file-not-found - possibly an embedding 
             situation - see if we can locate it in sys.prefix 
          */
        strncpy(modulepath, 
                ".", 
                sizeof(modulepath)/sizeof(modulepath[0]));
        if (modulepath[strlen(modulepath)-1] != '\\')
          strcat(modulepath, "\\");
        strncat(modulepath, 
                szConsoleSpawn, 
                (sizeof(modulepath)/sizeof(modulepath[0]))
                -strlen(modulepath));
        /* No where else to look - raise an easily identifiable
           error, rather than leaving Windows to report
           "file not found" - as the user is probably blissfully
           unaware this shim EXE is used, and it will confuse them.
           (well, it confused me for a while ;-)
        */
        if (stat(modulepath, &statinfo) != 0) 
          {
          std::cout 
            << "Can not locate '" << modulepath
            << "' which is needed "
            "for popen to work with your shell "
            "or platform." << std::endl;
          return FALSE;
          }
        }
      x = i + (int)strlen(s3) + (int)strlen(cmdstring) + 1 +
        (int)strlen(modulepath) + 
        (int)strlen(szConsoleSpawn) + 1;

      s2 = (char *)_alloca(x);
      ZeroMemory(s2, x);
      sprintf(
        s2,
        "%s %s%s%s",
        modulepath,
        s1,
        s3,
        cmdstring);
      sprintf(
        s2,
        "%s %s",
        modulepath,
        cmdstring);
      }
    }

  /* Could be an else here to try cmd.exe / command.com in the path
     Now we'll just error out.. */
  else 
    {
    std::cout << "Cannot locate a COMSPEC environment variable to "
              << "use as the shell" << std::endl;
    return FALSE;
    }
  
  ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
  siStartInfo.cb = sizeof(STARTUPINFO);
  siStartInfo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
  siStartInfo.hStdInput = hStdin;
  siStartInfo.hStdOutput = hStdout;
  siStartInfo.hStdError = hStderr;
  siStartInfo.wShowWindow = SW_HIDE;

  //std::cout << "Create process: " << s2 << std::endl;
  if (CreateProcess(NULL,
                    s2,
                    NULL,
                    NULL,
                    TRUE,
                    CREATE_NEW_CONSOLE,
                    NULL,
                    path,
                    &siStartInfo,
                    &piProcInfo) ) 
    {
    /* Close the handles now so anyone waiting is woken. */
    CloseHandle(piProcInfo.hThread);
    /* Return process handle */
    *hProcess = piProcInfo.hProcess;
    //std::cout << "Process created..." << std::endl;
    return TRUE;
    }
  win32_error("CreateProcess", s2);
  return FALSE;
}