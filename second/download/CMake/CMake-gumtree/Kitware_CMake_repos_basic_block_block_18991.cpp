{
    q = QUEUE_HEAD(&loop->cf_signals);
    s = QUEUE_DATA(q, uv__cf_loop_signal_t, member);
    QUEUE_REMOVE(q);
    uv__free(s);
  }