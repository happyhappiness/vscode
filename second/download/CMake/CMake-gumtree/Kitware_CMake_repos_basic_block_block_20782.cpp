{
    case UV_TCP:
      err = uv_tcp_listen((uv_tcp_t*)stream, backlog, cb);
      break;
    case UV_NAMED_PIPE:
      err = uv_pipe_listen((uv_pipe_t*)stream, backlog, cb);
      break;
    default:
      assert(0);
  }