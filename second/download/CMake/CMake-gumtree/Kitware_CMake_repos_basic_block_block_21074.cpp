{
    SET_REQ_SUCCESS(req);
    req->u.io.overlapped.InternalHigh = 0;
    POST_COMPLETION_FOR_REQ(loop, req);
    return 0;
  }