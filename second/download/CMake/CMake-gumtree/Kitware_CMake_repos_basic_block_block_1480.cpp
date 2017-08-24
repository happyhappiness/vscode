{
      /* The query succeeded.  Initialize traversal of the process list.  */
      self->CurrentInfo = (PSYSTEM_PROCESS_INFORMATION)self->Buffer;
      return 1;
    }