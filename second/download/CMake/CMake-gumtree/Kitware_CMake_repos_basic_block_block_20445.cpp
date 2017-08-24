(i = 0; i < handle->pipe.serv.pending_instances; i++) {
    uv_pipe_queue_accept(loop, handle, &handle->pipe.serv.accept_reqs[i], i == 0);
  }