{
    case UV_NAMED_PIPE:
      err = uv_pipe_write2(loop,
                           req,
                           (uv_pipe_t*) handle,
                           bufs,
                           nbufs,
                           send_handle,
                           cb);
      break;
    default:
      assert(0);
  }