{
      assert(rfds.fd_count == 1);
      assert(rfds.fd_array[0] == handle->socket);
      reported_events |= UV_READABLE;
    }