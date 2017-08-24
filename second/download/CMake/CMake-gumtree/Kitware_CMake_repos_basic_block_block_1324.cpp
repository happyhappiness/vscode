(cp->Detached) {
      kwsysProcess_Disown(cp);
    } else {
      kwsysProcess_WaitForExit(cp, 0);
    }