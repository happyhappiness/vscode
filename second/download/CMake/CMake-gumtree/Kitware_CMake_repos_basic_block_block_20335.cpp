{
    assert(req->retcode == 0);
    req->retcode = UV_EAI_CANCELED;
    goto complete;
  }