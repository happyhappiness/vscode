(((n = read(cp->PipeReadEnds[i], cp->PipeBuffer,
                        KWSYSPE_PIPE_BUFFER_SIZE)) < 0) &&
             (errno == EINTR))
        ;