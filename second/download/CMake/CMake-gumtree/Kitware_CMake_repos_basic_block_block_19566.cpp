{
    q = QUEUE_HEAD(&stream->write_queue);
    QUEUE_REMOVE(q);

    req = QUEUE_DATA(q, uv_write_t, queue);
    req->error = error;

    QUEUE_INSERT_TAIL(&stream->write_completed_queue, &req->queue);
  }