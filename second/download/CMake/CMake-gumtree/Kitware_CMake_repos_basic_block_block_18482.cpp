{
      QUEUE_REMOVE(q);
      QUEUE_INIT(q);  /* Signal uv_cancel() that the work req is
                             executing. */
    }