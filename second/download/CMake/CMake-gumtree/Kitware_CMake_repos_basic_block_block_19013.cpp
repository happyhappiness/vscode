{
  size_t hostname_len;
  size_t service_len;
  size_t hints_len;
  size_t len;
  char* buf;

  if (req == NULL || (hostname == NULL && service == NULL))
    return -EINVAL;

  hostname_len = hostname ? strlen(hostname) + 1 : 0;
  service_len = service ? strlen(service) + 1 : 0;
  hints_len = hints ? sizeof(*hints) : 0;
  buf = uv__malloc(hostname_len + service_len + hints_len);

  if (buf == NULL)
    return -ENOMEM;

  uv__req_init(loop, req, UV_GETADDRINFO);
  req->loop = loop;
  req->cb = cb;
  req->addrinfo = NULL;
  req->hints = NULL;
  req->service = NULL;
  req->hostname = NULL;
  req->retcode = 0;

  /* order matters, see uv_getaddrinfo_done() */
  len = 0;

  if (hints) {
    req->hints = memcpy(buf + len, hints, sizeof(*hints));
    len += sizeof(*hints);
  }

  if (service) {
    req->service = memcpy(buf + len, service, service_len);
    len += service_len;
  }

  if (hostname)
    req->hostname = memcpy(buf + len, hostname, hostname_len);

  if (cb) {
    uv__work_submit(loop,
                    &req->work_req,
                    uv__getaddrinfo_work,
                    uv__getaddrinfo_done);
    return 0;
  } else {
    uv__getaddrinfo_work(&req->work_req);
    uv__getaddrinfo_done(&req->work_req, 0);
    return req->retcode;
  }
}