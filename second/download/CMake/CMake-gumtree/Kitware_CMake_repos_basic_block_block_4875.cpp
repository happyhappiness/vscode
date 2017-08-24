f(t)
      /* the removed may have another timeout in queue */
      (void)add_next_timeout(now, multi, t->payload)