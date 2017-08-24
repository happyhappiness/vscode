{
    /* Windows 9x */
    
    /* The forwarding executable is given a handle to the error pipe
       and a handle to the kill event.  */
    cp->RealCommand = malloc(strlen(cp->Win9x)+strlen(cp->Command)+100);
    sprintf(cp->RealCommand, "%s %p %p %d %s", cp->Win9x,
            cp->Pipe[CMPE_PIPE_ERROR].Write, cp->Win9xKillEvent,
            cp->HideWindow, cp->Command);
    }