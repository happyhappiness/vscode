{
  if (req == NULL || addr == NULL)
    return UV_EINVAL;

  if (addr->sa_family == AF_INET) {
    memcpy(&req->storage,
           addr,
           sizeof(struct sockaddr_in));
  } else if (addr->sa_family == AF_INET6) {
    memcpy(&req->storage,
           addr,
           sizeof(struct sockaddr_in6));
  } else {
    return UV_EINVAL;
  }

  UV_REQ_INIT(req, UV_GETNAMEINFO);
  uv__req_register(loop, req);

  req->getnameinfo_cb = getnameinfo_cb;
  req->flags = flags;
  req->loop = loop;
  req->retcode = 0;

  if (getnameinfo_cb) {
    uv__work_submit(loop,
                    &req->work_req,
                    uv__getnameinfo_work,
                    uv__getnameinfo_done);
    return 0;
  } else {
    uv__getnameinfo_work(&req->work_req);
    uv__getnameinfo_done(&req->work_req, 0);
    return req->retcode;
  }
}