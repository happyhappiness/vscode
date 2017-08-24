(i = 0; i < cp->NumberOfCommands; ++i) {
    cp->ForkPIDs[i] = 0; /* can't use memset due to volatile */
  }