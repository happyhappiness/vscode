(((result = waitpid(cp->ForkPIDs[i], &cp->CommandExitCodes[i],
                                WNOHANG)) < 0) &&
             (errno == EINTR))
        ;