sprintf(cp->RealCommand, "%s %p %p %d %s", cp->Win9x,
            cp->Pipe[CMPE_PIPE_ERROR].Write, cp->Win9xKillEvent,
            cp->HideWindow, cp->Command);