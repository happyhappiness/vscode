(stream->type) {
    case UV_TCP:
      return uv__tcp_try_write((uv_tcp_t*) stream, bufs, nbufs);
    case UV_TTY:
      return uv__tty_try_write((uv_tty_t*) stream, bufs, nbufs);
    case UV_NAMED_PIPE:
      return UV_EAGAIN;
    default:
      assert(0);
      return UV_ENOSYS;
  }