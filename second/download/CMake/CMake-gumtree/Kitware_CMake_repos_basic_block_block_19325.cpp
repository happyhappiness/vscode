{
      assert(timeout != -1);
      timeout = real_timeout - timeout;
      if (timeout > 0)
        continue;

      return;
    }