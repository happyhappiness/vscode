{
    assert(handle->stream.conn.write_reqs_pending > 0);
    uv_queue_non_overlapped_write(handle);
  }