    char tempDir[_MAX_PATH+1] = "";
    
    /* We will try putting the executable in the system temp
       directory.  */
    DWORD length = GetEnvironmentVariable("TEMP", tempDir, _MAX_PATH);
    
    /* Construct the executable name from the process id and kwsysProcess
       instance.  This should be unique.  */
    sprintf(fwdName, "cmw9xfwd_%u_%p.exe", GetCurrentProcessId(), cp);
    
    /* If the environment variable "TEMP" gave us a directory, use it.  */
    if(length > 0 && length <= _MAX_PATH)
      {
      /* Make sure there is no trailing slash.  */
      size_t tdlen = strlen(tempDir);
      if(tempDir[tdlen-1] == '/' || tempDir[tdlen-1] == '\\')
        {
        tempDir[tdlen-1] = 0;
        --tdlen;
        }
      
      /* Allocate a buffer to hold the forwarding executable path.  */
      win9x = (char*)malloc(tdlen + strlen(fwdName) + 2);
      if(!win9x)
        {
