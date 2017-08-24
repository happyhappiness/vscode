{
        assert(!(handle->flags & UV_CLOSING));
        handle->signal_cb(handle, handle->signum);
      }