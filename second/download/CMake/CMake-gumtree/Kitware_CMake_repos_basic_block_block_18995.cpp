{
    item = QUEUE_HEAD(&split_head);
    QUEUE_REMOVE(item);

    s = QUEUE_DATA(item, uv__cf_loop_signal_t, member);

    /* This was a termination signal */
    if (s->handle == NULL)
      pCFRunLoopStop(state->loop);
    else
      uv__fsevents_reschedule(s->handle, s->type);

    uv__free(s);
  }