snprintf(pipe_name, sizeof(pipe_name),
           "\\\\.\\pipe\\ninja_pid%u_sp%p", GetCurrentProcessId(), this);