{
    case UV_TCP:
      err = uv_tcp_read_start((uv_tcp_t*)handle, alloc_cb, read_cb);
      break;
    case UV_NAMED_PIPE:
      err = uv_pipe_read_start((uv_pipe_t*)handle, alloc_cb, read_cb);
      break;
    case UV_TTY:
      err = uv_tty_read_start((uv_tty_t*) handle, alloc_cb, read_cb);
      break;
    default:
      assert(0);
  }