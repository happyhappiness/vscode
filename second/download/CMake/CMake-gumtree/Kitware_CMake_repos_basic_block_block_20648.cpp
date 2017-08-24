{
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