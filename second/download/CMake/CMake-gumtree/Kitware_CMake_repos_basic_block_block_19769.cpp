(domain != AF_UNSPEC) {
    int err = maybe_new_socket(tcp, domain, 0);
    if (err) {
      QUEUE_REMOVE(&tcp->handle_queue);
      return err;
    }
  }