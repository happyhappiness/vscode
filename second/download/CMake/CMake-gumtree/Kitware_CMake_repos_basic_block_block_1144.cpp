(!kwsysProcessSetupOutputPipeFile(&cp->PipeChildStd[1],
                                         cp->PipeFileSTDOUT)) {
      kwsysProcessCleanup(cp, 1);
      return;
    }