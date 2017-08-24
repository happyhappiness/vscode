{
    req->hints = memcpy(buf + len, hints, sizeof(*hints));
    len += sizeof(*hints);
  }