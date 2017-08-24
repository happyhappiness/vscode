{
  case UV_TCP:
  case UV_NAMED_PIPE:
  case UV_TTY:
    fd_out = uv__stream_fd((uv_stream_t*) handle);
    break;

  case UV_UDP:
    fd_out = ((uv_udp_t *) handle)->io_watcher.fd;
    break;

  case UV_POLL:
    fd_out = ((uv_poll_t *) handle)->io_watcher.fd;
    break;

  default:
    return -EINVAL;
  }