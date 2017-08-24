{
    q = QUEUE_HEAD(&handle->write_queue);
    QUEUE_REMOVE(q);

    req = QUEUE_DATA(q, uv_udp_send_t, queue);
    req->status = -ECANCELED;
    QUEUE_INSERT_TAIL(&handle->write_completed_queue, &req->queue);
  }