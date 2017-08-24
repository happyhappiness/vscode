{
      /* This should never happen, and if it happens, we can't recover... */
      uv_fatal_error(GetLastError(), "UnregisterWaitEx");
    }