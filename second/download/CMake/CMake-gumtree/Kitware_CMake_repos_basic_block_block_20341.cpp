{
  int nodesize = 0;
  int servicesize = 0;
  int hintssize = 0;
  char* alloc_ptr = NULL;
  int err;

  if (req == NULL || (node == NULL && service == NULL)) {
    return UV_EINVAL;
  }

  UV_REQ_INIT(req, UV_GETADDRINFO);
  req->getaddrinfo_cb = getaddrinfo_cb;
  req->addrinfo = NULL;
  req->loop = loop;
  req->retcode = 0;

  /* calculate required memory size for all input values */
  if (node != NULL) {
    nodesize = ALIGNED_SIZE(MultiByteToWideChar(CP_UTF8, 0, node, -1, NULL, 0) *
                            sizeof(WCHAR));
    if (nodesize == 0) {
      err = GetLastError();
      goto error;
    }
  }

  if (service != NULL) {
    servicesize = ALIGNED_SIZE(MultiByteToWideChar(CP_UTF8,
                                                   0,
                                                   service,
                                                   -1,
                                                   NULL,
                                                   0) *
                               sizeof(WCHAR));
    if (servicesize == 0) {
      err = GetLastError();
      goto error;
    }
  }
  if (hints != NULL) {
    hintssize = ALIGNED_SIZE(sizeof(struct addrinfoW));
  }

  /* allocate memory for inputs, and partition it as needed */
  alloc_ptr = (char*)uv__malloc(nodesize + servicesize + hintssize);
  if (!alloc_ptr) {
    err = WSAENOBUFS;
    goto error;
  }

  /* save alloc_ptr now so we can free if error */
  req->alloc = (void*)alloc_ptr;

  /* convert node string to UTF16 into allocated memory and save pointer in */
  /* the request. */
  if (node != NULL) {
    req->node = (WCHAR*)alloc_ptr;
    if (MultiByteToWideChar(CP_UTF8,
                            0,
                            node,
                            -1,
                            (WCHAR*) alloc_ptr,
                            nodesize / sizeof(WCHAR)) == 0) {
      err = GetLastError();
      goto error;
    }
    alloc_ptr += nodesize;
  } else {
    req->node = NULL;
  }

  /* convert service string to UTF16 into allocated memory and save pointer */
  /* in the req. */
  if (service != NULL) {
    req->service = (WCHAR*)alloc_ptr;
    if (MultiByteToWideChar(CP_UTF8,
                            0,
                            service,
                            -1,
                            (WCHAR*) alloc_ptr,
                            servicesize / sizeof(WCHAR)) == 0) {
      err = GetLastError();
      goto error;
    }
    alloc_ptr += servicesize;
  } else {
    req->service = NULL;
  }

  /* copy hints to allocated memory and save pointer in req */
  if (hints != NULL) {
    req->addrinfow = (struct addrinfoW*)alloc_ptr;
    req->addrinfow->ai_family = hints->ai_family;
    req->addrinfow->ai_socktype = hints->ai_socktype;
    req->addrinfow->ai_protocol = hints->ai_protocol;
    req->addrinfow->ai_flags = hints->ai_flags;
    req->addrinfow->ai_addrlen = 0;
    req->addrinfow->ai_canonname = NULL;
    req->addrinfow->ai_addr = NULL;
    req->addrinfow->ai_next = NULL;
  } else {
    req->addrinfow = NULL;
  }

  uv__req_register(loop, req);

  if (getaddrinfo_cb) {
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

error:
  if (req != NULL) {
    uv__free(req->alloc);
    req->alloc = NULL;
  }
  return uv_translate_sys_error(err);
}