{
    /* We cannot start another CFRunloop and/or thread in the child
       process; CF aborts if you try or if you try to touch the thread
       at all to kill it. So the best we can do is ignore it from now
       on. This means we can't watch directories in the same way
       anymore (like other BSDs). It also means we cannot properly
       clean up the allocated resources; calling
       uv__fsevents_loop_delete from uv_loop_close will crash the
       process. So we sidestep the issue by pretending like we never
       started it in the first place.
    */
    uv__has_forked_with_cfrunloop = 1;
    uv__free(loop->cf_state);
    loop->cf_state = NULL;
  }