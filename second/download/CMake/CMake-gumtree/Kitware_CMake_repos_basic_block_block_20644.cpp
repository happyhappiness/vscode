(stream->type == UV_NAMED_PIPE &&
                   stream->flags & UV_HANDLE_CONNECTION) {
          stream_handle = ((uv_pipe_t*) stream)->handle;
          crt_flags = FOPEN | FPIPE;
        }