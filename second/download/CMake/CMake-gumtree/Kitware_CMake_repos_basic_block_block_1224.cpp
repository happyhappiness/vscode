(cp->ForkPIDs[i]) {
          /* Kill the child.  */
          kwsysProcessKill(cp->ForkPIDs[i]);

          /* Reap the child.  Keep trying until the call is not
             interrupted.  */
          while ((waitpid(cp->ForkPIDs[i], &status, 0) < 0) &&
                 (errno == EINTR))
            ;
        }