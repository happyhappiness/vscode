(i = 0; i < cp->NumberOfCommands; ++i) {
        /* Make sure the PID is still valid. */
        if (cp->ForkPIDs[i]) {
          /* The user created a process group for this process.  The group ID
             is the process ID for the original process in the group.  */
          kill(-cp->ForkPIDs[i], SIGINT);
        }
      }