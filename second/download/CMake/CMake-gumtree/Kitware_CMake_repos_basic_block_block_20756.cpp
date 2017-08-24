{
    req->next_req = req;
    loop->pending_reqs_tail = req;
  }