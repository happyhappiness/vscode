{
      assert(handle->pipe.serv.accept_reqs);
      uv__free(handle->pipe.serv.accept_reqs);
      handle->pipe.serv.accept_reqs = NULL;
    }