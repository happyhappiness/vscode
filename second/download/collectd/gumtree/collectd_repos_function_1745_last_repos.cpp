static void *ovs_poll_worker(void *arg) {
  ovs_db_t *pdb = (ovs_db_t *)arg; /* pointer to OVS DB */
  ovs_json_reader_t *jreader = NULL;
  struct pollfd poll_fd = {
      .fd = pdb->sock, .events = POLLIN | POLLPRI, .revents = 0,
  };

  /* create JSON reader instance */
  if ((jreader = ovs_json_reader_alloc()) == NULL) {
    OVS_ERROR("initialize json reader failed");
    return NULL;
  }

  /* poll data */
  while (ovs_db_poll_is_running(pdb)) {
    char errbuff[OVS_ERROR_BUFF_SIZE];
    poll_fd.fd = pdb->sock;
    int poll_ret = poll(&poll_fd, 1, /* ms */ OVS_DB_POLL_TIMEOUT * 1000);
    if (poll_ret < 0) {
      sstrerror(errno, errbuff, sizeof(errbuff));
      OVS_ERROR("poll(): %s", errbuff);
      break;
    } else if (poll_ret == 0) {
      OVS_DEBUG("poll(): timeout");
      if (pdb->sock < 0)
        /* invalid fd, so try to reconnect */
        ovs_db_reconnect(pdb);
      continue;
    }
    if (poll_fd.revents & POLLNVAL) {
      /* invalid file descriptor, clean-up */
      ovs_db_callback_remove_all(pdb);
      ovs_json_reader_reset(jreader);
      /* setting poll FD to -1 tells poll() call to ignore this FD.
       * In that case poll() call will return timeout all the time */
      pdb->sock = (-1);
    } else if ((poll_fd.revents & POLLERR) || (poll_fd.revents & POLLHUP)) {
      /* connection is broken */
      close(poll_fd.fd);
      ovs_db_event_post(pdb, OVS_DB_EVENT_CONN_TERMINATED);
      OVS_ERROR("poll() peer closed its end of the channel");
    } else if ((poll_fd.revents & POLLIN) || (poll_fd.revents & POLLPRI)) {
      /* read incoming data */
      char buff[OVS_DB_POLL_READ_BLOCK_SIZE];
      ssize_t nbytes = recv(poll_fd.fd, buff, sizeof(buff), 0);
      if (nbytes < 0) {
        sstrerror(errno, errbuff, sizeof(errbuff));
        OVS_ERROR("recv(): %s", errbuff);
        /* read error? Try to reconnect */
        close(poll_fd.fd);
        continue;
      } else if (nbytes == 0) {
        close(poll_fd.fd);
        ovs_db_event_post(pdb, OVS_DB_EVENT_CONN_TERMINATED);
        OVS_ERROR("recv() peer has performed an orderly shutdown");
        continue;
      }
      /* read incoming data */
      size_t json_len = 0;
      const char *json = NULL;
      OVS_DEBUG("recv(): received %zd bytes of data", nbytes);
      ovs_json_reader_push_data(jreader, buff, nbytes);
      while (!ovs_json_reader_pop(jreader, &json, &json_len))
        /* process JSON data */
        ovs_db_json_data_process(pdb, json, json_len);
    }
  }

  OVS_DEBUG("poll thread has been completed");
  ovs_json_reader_free(jreader);
  return NULL;
}