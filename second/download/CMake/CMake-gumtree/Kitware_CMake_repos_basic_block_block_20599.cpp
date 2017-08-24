{
    /* Queue this req, reporting an error. */
    SET_REQ_ERROR(&handle->poll_req_1, WSAGetLastError());
    POST_COMPLETION_FOR_REQ(handle->loop, req);
    return 0;
  }