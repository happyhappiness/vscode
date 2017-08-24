{
      /* GetQueuedCompletionStatus can occasionally return a little early.
       * Make sure that the desired timeout target time is reached.
       */
      uv_update_time(loop);
      if (timeout_time > loop->time) {
        timeout = (DWORD)(timeout_time - loop->time);
        /* The first call to GetQueuedCompletionStatus should return very
         * close to the target time and the second should reach it, but
         * this is not stated in the documentation. To make sure a busy
         * loop cannot happen, the timeout is increased exponentially
         * starting on the third round.
         */
        timeout += repeat ? (1 << (repeat - 1)) : 0;
        continue;
      }
    }