{
      /* Request queued by the kernel. */
      req->u.io.queued_bytes = bufs[0].len;
      handle->write_queue_size += req->u.io.queued_bytes;
    }