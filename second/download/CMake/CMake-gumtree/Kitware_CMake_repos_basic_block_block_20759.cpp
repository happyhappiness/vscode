{
  uv_req_t* req;
  uv_req_t* first;
  uv_req_t* next;

  if (loop->pending_reqs_tail == NULL)
    return 0;

  first = loop->pending_reqs_tail->next_req;
  next = first;
  loop->pending_reqs_tail = NULL;

  while (next != NULL) {
    req = next;
    next = req->next_req != first ? req->next_req : NULL;

    switch (req->type) {
      case UV_READ:
        DELEGATE_STREAM_REQ(loop, req, read, data);
        break;

      case UV_WRITE:
        DELEGATE_STREAM_REQ(loop, (uv_write_t*) req, write, handle);
        break;

      case UV_ACCEPT:
        DELEGATE_STREAM_REQ(loop, req, accept, data);
        break;

      case UV_CONNECT:
        DELEGATE_STREAM_REQ(loop, (uv_connect_t*) req, connect, handle);
        break;

      case UV_SHUTDOWN:
        /* Tcp shutdown requests don't come here. */
        assert(((uv_shutdown_t*) req)->handle->type == UV_NAMED_PIPE);
        uv_process_pipe_shutdown_req(
            loop,
            (uv_pipe_t*) ((uv_shutdown_t*) req)->handle,
            (uv_shutdown_t*) req);
        break;

      case UV_UDP_RECV:
        uv_process_udp_recv_req(loop, (uv_udp_t*) req->data, req);
        break;

      case UV_UDP_SEND:
        uv_process_udp_send_req(loop,
                                ((uv_udp_send_t*) req)->handle,
                                (uv_udp_send_t*) req);
        break;

      case UV_WAKEUP:
        uv_process_async_wakeup_req(loop, (uv_async_t*) req->data, req);
        break;

      case UV_SIGNAL_REQ:
        uv_process_signal_req(loop, (uv_signal_t*) req->data, req);
        break;

      case UV_POLL_REQ:
        uv_process_poll_req(loop, (uv_poll_t*) req->data, req);
        break;

      case UV_PROCESS_EXIT:
        uv_process_proc_exit(loop, (uv_process_t*) req->data);
        break;

      case UV_FS_EVENT_REQ:
        uv_process_fs_event_req(loop, req, (uv_fs_event_t*) req->data);
        break;

      default:
        assert(0);
    }
  }

  return 1;
}