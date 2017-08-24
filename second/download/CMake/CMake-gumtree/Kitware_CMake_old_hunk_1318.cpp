    
    /* Construct the executable name from the process id and kwsysProcess
       instance.  This should be unique.  */
    sprintf(fwdName, "cmw9xfwd_%u_%p.exe", _getpid(), cp);
    
    /* If the environment variable "TEMP" gave us a directory, use it.  */
    if(length > 0 && length <= _MAX_PATH)
