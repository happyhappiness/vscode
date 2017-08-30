

    /* Construct the executable name from the process id and kwsysProcess

       instance.  This should be unique.  */

    sprintf(fwdName, KWSYS_NAMESPACE_STRING "pew9xfwd_%u_%p.exe",

            GetCurrentProcessId(), cp);



    /* If we have a temp directory, use it.  */

    if(length > 0 && length <= _MAX_PATH)

