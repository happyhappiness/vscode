{
    case UV_NAMED_PIPE:
    case UV_TCP:
      return ((uv_stream_t*) handle)->io_watcher.fd;

    case UV_UDP:
      return ((uv_udp_t*) handle)->io_watcher.fd;

    default:
      return -1;
  }