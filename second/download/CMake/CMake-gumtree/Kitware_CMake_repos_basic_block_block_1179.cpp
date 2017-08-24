{
        /* We are done reading from this pipe.  */
        kwsysProcessCleanupDescriptor(&cp->PipeReadEnds[i]);
        --cp->PipesLeft;
      }