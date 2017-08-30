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
        kwsysProcess_Delete(cp);
        return 0;
        }
      
      /* Construct the full path to the forwarding executable.  */
      sprintf(win9x, "%s/%s", tempDir, fwdName);
      }