(wfds.fd_count > 0) {
      assert(wfds.fd_count == 1);
      assert(wfds.fd_array[0] == handle->socket);
      reported_events |= UV_WRITABLE;
    } else if (efds.fd_count > 0) {
      assert(efds.fd_count == 1);
      assert(efds.fd_array[0] == handle->socket);
      reported_events |= UV_WRITABLE;
    }