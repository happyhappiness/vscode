static int cconn_handle_event(struct cconn *io) {
  int ret;
  switch (io->state) {
  case CSTATE_UNCONNECTED:
    ERROR("ceph plugin: cconn_handle_event(name=%s) got to illegal "
          "state on line %d",
          io->d->name, __LINE__);

    return -EDOM;
  case CSTATE_WRITE_REQUEST: {
    char cmd[32];
    snprintf(cmd, sizeof(cmd), "%s%d%s", "{ \"prefix\": \"", io->request_type,
             "\" }\n");
    size_t cmd_len = strlen(cmd);
    RETRY_ON_EINTR(
        ret, write(io->asok, ((char *)&cmd) + io->amt, cmd_len - io->amt));
    DEBUG("ceph plugin: cconn_handle_event(name=%s,state=%d,amt=%d,ret=%d)",
          io->d->name, io->state, io->amt, ret);
    if (ret < 0) {
      return ret;
    }
    io->amt += ret;
    if (io->amt >= cmd_len) {
      io->amt = 0;
      switch (io->request_type) {
      case ASOK_REQ_VERSION:
        io->state = CSTATE_READ_VERSION;
        break;
      default:
        io->state = CSTATE_READ_AMT;
        break;
      }
    }
    return 0;
  }
  case CSTATE_READ_VERSION: {
    RETRY_ON_EINTR(ret, read(io->asok, ((char *)(&io->d->version)) + io->amt,
                             sizeof(io->d->version) - io->amt));
    DEBUG("ceph plugin: cconn_handle_event(name=%s,state=%d,ret=%d)",
          io->d->name, io->state, ret);
    if (ret < 0) {
      return ret;
    }
    io->amt += ret;
    if (io->amt >= sizeof(io->d->version)) {
      io->d->version = ntohl(io->d->version);
      if (io->d->version != 1) {
        ERROR("ceph plugin: cconn_handle_event(name=%s) not "
              "expecting version %d!",
              io->d->name, io->d->version);
        return -ENOTSUP;
      }
      DEBUG("ceph plugin: cconn_handle_event(name=%s): identified as "
            "version %d",
            io->d->name, io->d->version);
      io->amt = 0;
      cconn_close(io);
      io->request_type = ASOK_REQ_SCHEMA;
    }
    return 0;
  }
  case CSTATE_READ_AMT: {
    RETRY_ON_EINTR(ret, read(io->asok, ((char *)(&io->json_len)) + io->amt,
                             sizeof(io->json_len) - io->amt));
    DEBUG("ceph plugin: cconn_handle_event(name=%s,state=%d,ret=%d)",
          io->d->name, io->state, ret);
    if (ret < 0) {
      return ret;
    }
    io->amt += ret;
    if (io->amt >= sizeof(io->json_len)) {
      io->json_len = ntohl(io->json_len);
      io->amt = 0;
      io->state = CSTATE_READ_JSON;
      io->json = calloc(1, io->json_len + 1);
      if (!io->json) {
        ERROR("ceph plugin: error callocing io->json");
        return -ENOMEM;
      }
    }
    return 0;
  }
  case CSTATE_READ_JSON: {
    RETRY_ON_EINTR(ret,
                   read(io->asok, io->json + io->amt, io->json_len - io->amt));
    DEBUG("ceph plugin: cconn_handle_event(name=%s,state=%d,ret=%d)",
          io->d->name, io->state, ret);
    if (ret < 0) {
      return ret;
    }
    io->amt += ret;
    if (io->amt >= io->json_len) {
      ret = cconn_process_json(io);
      if (ret) {
        return ret;
      }
      cconn_close(io);
      io->request_type = ASOK_REQ_NONE;
    }
    return 0;
  }
  default:
    ERROR("ceph plugin: cconn_handle_event(name=%s) got to illegal "
          "state on line %d",
          io->d->name, __LINE__);
    return -EDOM;
  }
}