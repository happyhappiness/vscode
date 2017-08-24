{
  uv_req_t* req;
  AFD_POLL_INFO* afd_poll_info;
  DWORD result;

  /* Find a yet unsubmitted req to submit. */
  if (handle->submitted_events_1 == 0) {
    req = &handle->poll_req_1;
    afd_poll_info = &handle->afd_poll_info_1;
    handle->submitted_events_1 = handle->events;
    handle->mask_events_1 = 0;
    handle->mask_events_2 = handle->events;
  } else if (handle->submitted_events_2 == 0) {
    req = &handle->poll_req_2;
    afd_poll_info = &handle->afd_poll_info_2;
    handle->submitted_events_2 = handle->events;
    handle->mask_events_1 = handle->events;
    handle->mask_events_2 = 0;
  } else {
    /* Just wait until there's an unsubmitted req. */
    /* This will happen almost immediately as one of the 2 outstanding */
    /* requests is about to return. When this happens, */
    /* uv__fast_poll_process_poll_req will be called, and the pending */
    /* events, if needed, will be processed in a subsequent request. */
    return;
  }

  /* Setting Exclusive to TRUE makes the other poll request return if there */
  /* is any. */
  afd_poll_info->Exclusive = TRUE;
  afd_poll_info->NumberOfHandles = 1;
  afd_poll_info->Timeout.QuadPart = INT64_MAX;
  afd_poll_info->Handles[0].Handle = (HANDLE) handle->socket;
  afd_poll_info->Handles[0].Status = 0;
  afd_poll_info->Handles[0].Events = 0;

  if (handle->events & UV_READABLE) {
    afd_poll_info->Handles[0].Events |= AFD_POLL_RECEIVE |
        AFD_POLL_DISCONNECT | AFD_POLL_ACCEPT | AFD_POLL_ABORT;
  } else {
    if (handle->events & UV_DISCONNECT) {
      afd_poll_info->Handles[0].Events |= AFD_POLL_DISCONNECT;
    }
  }
  if (handle->events & UV_WRITABLE) {
    afd_poll_info->Handles[0].Events |= AFD_POLL_SEND | AFD_POLL_CONNECT_FAIL;
  }

  memset(&req->u.io.overlapped, 0, sizeof req->u.io.overlapped);

  result = uv_msafd_poll((SOCKET) handle->peer_socket,
                         afd_poll_info,
                         afd_poll_info,
                         &req->u.io.overlapped);
  if (result != 0 && WSAGetLastError() != WSA_IO_PENDING) {
    /* Queue this req, reporting an error. */
    SET_REQ_ERROR(req, WSAGetLastError());
    uv_insert_pending_req(loop, req);
  }
}