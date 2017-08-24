(kwsysProcess_List_GetCurrentParentId(plist) == pid) {
        int ppid = kwsysProcess_List_GetCurrentProcessId(plist);
        kwsysProcessKillTree(ppid);
      }