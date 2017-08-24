(!uv_get_acceptex_function(handle->socket, &handle->tcp.serv.func_acceptex)) {
      return WSAEAFNOSUPPORT;
    }