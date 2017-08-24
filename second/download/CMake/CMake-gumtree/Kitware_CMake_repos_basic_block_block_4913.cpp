{
      data = t->payload; /* assign this for next loop */
      (void)add_next_timeout(now, multi, t->payload);
    }