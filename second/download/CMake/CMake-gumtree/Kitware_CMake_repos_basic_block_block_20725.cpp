(fdopt->flags & UV_CREATE_PIPE &&
        fdopt->data.stream->type == UV_NAMED_PIPE &&
        ((uv_pipe_t*) fdopt->data.stream)->ipc) {
      ((uv_pipe_t*) fdopt->data.stream)->pipe.conn.ipc_pid = info.dwProcessId;
    }