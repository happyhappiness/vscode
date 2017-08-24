{
      assert(wfds.fd_count == 1);
      assert(wfds.fd_array[0] == handle->socket);
      reported_events |= UV_WRITABLE;
    }