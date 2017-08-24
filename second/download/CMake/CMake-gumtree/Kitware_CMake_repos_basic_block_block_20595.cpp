{
      assert(efds.fd_count == 1);
      assert(efds.fd_array[0] == handle->socket);
      reported_events |= UV_WRITABLE;
    }