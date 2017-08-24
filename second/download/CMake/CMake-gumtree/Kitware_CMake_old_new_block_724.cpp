{
    snprintf(cp->ErrorMessage, KWSYSPE_PIPE_BUFFER_SIZE, "%s", strerror(errno));
    cp->State = kwsysProcess_State_Error;
    }