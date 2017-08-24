{
        /* Use an existing stream as the stdio handle for the child. */
        HANDLE stream_handle, child_handle;
        unsigned char crt_flags;
        uv_stream_t* stream = fdopt.data.stream;

        /* Leech the handle out of the stream. */
        if (stream->type == UV_TTY) {
          stream_handle = ((uv_tty_t*) stream)->handle;
          crt_flags = FOPEN | FDEV;
        } else if (stream->type == UV_NAMED_PIPE &&
                   stream->flags & UV_HANDLE_CONNECTION) {
          stream_handle = ((uv_pipe_t*) stream)->handle;
          crt_flags = FOPEN | FPIPE;
        } else {
          stream_handle = INVALID_HANDLE_VALUE;
          crt_flags = 0;
        }

        if (stream_handle == NULL ||
            stream_handle == INVALID_HANDLE_VALUE) {
          /* The handle is already closed, or not yet created, or the */
          /* stream type is not supported. */
          err = ERROR_NOT_SUPPORTED;
          goto error;
        }

        /* Make an inheritable copy of the handle. */
        err = uv__duplicate_handle(loop, stream_handle, &child_handle);
        if (err)
          goto error;

        CHILD_STDIO_HANDLE(buffer, i) = child_handle;
        CHILD_STDIO_CRT_FLAGS(buffer, i) = crt_flags;
        break;
      }