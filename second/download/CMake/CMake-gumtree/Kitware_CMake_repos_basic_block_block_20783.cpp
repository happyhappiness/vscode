{
    case UV_TCP:
      err = uv_tcp_accept((uv_tcp_t*)server, (uv_tcp_t*)client);
      break;
    case UV_NAMED_PIPE:
      err = uv_pipe_accept((uv_pipe_t*)server, client);
      break;
    default:
      assert(0);
  }