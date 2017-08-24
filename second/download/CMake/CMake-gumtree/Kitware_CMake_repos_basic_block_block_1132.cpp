(si.StdIn != cp->PipeChildStd[0]) {
          kwsysProcessCleanupDescriptor(&si.StdIn);
        }