{
        int ppid = kwsysProcess_List_GetCurrentProcessId(plist);
        kwsysProcessKillTree(ppid);
      }