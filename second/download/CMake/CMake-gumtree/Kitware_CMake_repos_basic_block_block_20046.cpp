{
      /* Package was dequeued */
      req = uv_overlapped_to_req(overlapped);
      uv_insert_pending_req(loop, req);

      /* Some time might have passed waiting for I/O,
       * so update the loop time here.
       */
      uv_update_time(loop);
    }