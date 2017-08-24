(cp->PipeNativeSTDERR[1] >= 0) {
    /* Use the given handle for stderr.  */
    if (!kwsysProcessSetupOutputPipeNative(&cp->PipeChildStd[2],
                                           cp->PipeNativeSTDERR)) {
      kwsysProcessCleanup(cp, 1);
      return;
    }
  }