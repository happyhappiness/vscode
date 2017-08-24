{
    uv_stdio_container_t fdopt;
    if (i < options->stdio_count) {
      fdopt = options->stdio[i];
    } else {
      fdopt.flags = UV_IGNORE;
    }

    switch (fdopt.flags & (UV_IGNORE | UV_CREATE_PIPE | UV_INHERIT_FD |
            UV_INHERIT_STREAM)) {
      case UV_IGNORE:
        /* Starting a process with no stdin/stout/stderr can confuse it. */
        /* So no matter what the user specified, we make sure the first */
        /* three FDs are always open in their typical modes, e.g. stdin */
        /* be readable and stdout/err should be writable. For FDs > 2, don't */
        /* do anything - all handles in the stdio buffer are initialized with */
        /* INVALID_HANDLE_VALUE, which should be okay. */
        if (i <= 2) {
          DWORD access = (i == 0) ? FILE_GENERIC_READ :
                                    FILE_GENERIC_WRITE | FILE_READ_ATTRIBUTES;

          err = uv__create_nul_handle(&CHILD_STDIO_HANDLE(buffer, i),
                                      access);
          if (err)
            goto error;

          CHILD_STDIO_CRT_FLAGS(buffer, i) = FOPEN | FDEV;
        }
        break;

      case UV_CREATE_PIPE: {
        /* Create a pair of two connected pipe ends; one end is turned into */
        /* an uv_pipe_t for use by the parent. The other one is given to */
        /* the child. */
        uv_pipe_t* parent_pipe = (uv_pipe_t*) fdopt.data.stream;
        HANDLE child_pipe = INVALID_HANDLE_VALUE;

        /* Create a new, connected pipe pair. stdio[i].stream should point */
        /* to an uninitialized, but not connected pipe handle. */
        assert(fdopt.data.stream->type == UV_NAMED_PIPE);
        assert(!(fdopt.data.stream->flags & UV_HANDLE_CONNECTION));
        assert(!(fdopt.data.stream->flags & UV_HANDLE_PIPESERVER));

        err = uv__create_stdio_pipe_pair(loop,
                                         parent_pipe,
                                         &child_pipe,
                                         fdopt.flags);
        if (err)
          goto error;

        CHILD_STDIO_HANDLE(buffer, i) = child_pipe;
        CHILD_STDIO_CRT_FLAGS(buffer, i) = FOPEN | FPIPE;
        break;
      }

      case UV_INHERIT_FD: {
        /* Inherit a raw FD. */
        HANDLE child_handle;

        /* Make an inheritable duplicate of the handle. */
        err = uv__duplicate_fd(loop, fdopt.data.fd, &child_handle);
        if (err) {
          /* If fdopt.data.fd is not valid and fd fd <= 2, then ignore the */
          /* error. */
          if (fdopt.data.fd <= 2 && err == ERROR_INVALID_HANDLE) {
            CHILD_STDIO_CRT_FLAGS(buffer, i) = 0;
            CHILD_STDIO_HANDLE(buffer, i) = INVALID_HANDLE_VALUE;
            break;
          }
          goto error;
        }

        /* Figure out what the type is. */
        switch (GetFileType(child_handle)) {
          case FILE_TYPE_DISK:
            CHILD_STDIO_CRT_FLAGS(buffer, i) = FOPEN;
            break;

          case FILE_TYPE_PIPE:
            CHILD_STDIO_CRT_FLAGS(buffer, i) = FOPEN | FPIPE;
            break;

          case FILE_TYPE_CHAR:
          case FILE_TYPE_REMOTE:
            CHILD_STDIO_CRT_FLAGS(buffer, i) = FOPEN | FDEV;
            break;

          case FILE_TYPE_UNKNOWN:
            if (GetLastError() != 0) {
              err = GetLastError();
              CloseHandle(child_handle);
              goto error;
            }
            CHILD_STDIO_CRT_FLAGS(buffer, i) = FOPEN | FDEV;
            break;

          default:
            assert(0);
            return -1;
        }

        CHILD_STDIO_HANDLE(buffer, i) = child_handle;
        break;
      }

      case UV_INHERIT_STREAM: {
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

      default:
        assert(0);
        return -1;
    }
  }