{
    case UV_TCP:
      err = uv_tcp_write(loop, req, (uv_tcp_t*) handle, bufs, nbufs, cb);
      break;
    case UV_NAMED_PIPE:
      err = uv_pipe_write(loop, req, (uv_pipe_t*) handle, bufs, nbufs, cb);
      break;
    case UV_TTY:
      err = uv_tty_write(loop, req, (uv_tty_t*) handle, bufs, nbufs, cb);
      break;
    default:
      assert(0);
  }