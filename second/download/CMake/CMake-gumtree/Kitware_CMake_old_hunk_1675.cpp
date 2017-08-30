       work-around a Windows 9x bug.  */

    char fwdName[_MAX_FNAME+1] = "";

    char tempDir[_MAX_PATH+1] = "";

    

    /* We will try putting the executable in the system temp

       directory.  Note that the returned path already has a trailing

       slash.  */

    DWORD length = GetTempPath(_MAX_PATH+1, tempDir);

    

    /* Construct the executable name from the process id and kwsysProcess

       instance.  This should be unique.  */

    sprintf(fwdName, "cmw9xfwd_%u_%p.exe", GetCurrentProcessId(), cp);

    

    /* If we have a temp directory, use it.  */

    if(length > 0 && length <= _MAX_PATH)

      {

