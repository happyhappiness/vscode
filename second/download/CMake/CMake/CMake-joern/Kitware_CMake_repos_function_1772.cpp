static int uv__stream_recv_cmsg(uv_stream_t* stream, struct msghdr* msg) {
  struct cmsghdr* cmsg;

  for (cmsg = CMSG_FIRSTHDR(msg); cmsg != NULL; cmsg = CMSG_NXTHDR(msg, cmsg)) {
    char* start;
    char* end;
    int err;
    void* pv;
    int* pi;
    unsigned int i;
    unsigned int count;

    if (cmsg->cmsg_type != SCM_RIGHTS) {
      fprintf(stderr, "ignoring non-SCM_RIGHTS ancillary data: %d\n",
          cmsg->cmsg_type);
      continue;
    }

    /* silence aliasing warning */
    pv = CMSG_DATA(cmsg);
    pi = pv;

    /* Count available fds */
    start = (char*) cmsg;
    end = (char*) cmsg + cmsg->cmsg_len;
    count = 0;
    while (start + CMSG_LEN(count * sizeof(*pi)) < end)
      count++;
    assert(start + CMSG_LEN(count * sizeof(*pi)) == end);

    for (i = 0; i < count; i++) {
      /* Already has accepted fd, queue now */
      if (stream->accepted_fd != -1) {
        err = uv__stream_queue_fd(stream, pi[i]);
        if (err != 0) {
          /* Close rest */
          for (; i < count; i++)
            uv__close(pi[i]);
          return err;
        }
      } else {
        stream->accepted_fd = pi[i];
      }
    }
  }

  return 0;
}