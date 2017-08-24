{
      ret = uv__signal_register_handler(handle->signum, 1);
      assert(ret == 0);
    }