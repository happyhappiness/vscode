(!kwsysProcessSetupOutputPipeNative(&cp->PipeChildStd[2],
                                           cp->PipeNativeSTDERR)) {
      kwsysProcessCleanup(cp, 1);
      return;
    }