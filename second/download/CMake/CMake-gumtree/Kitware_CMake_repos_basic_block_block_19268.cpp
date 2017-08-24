{
    epoll_queue_close(loop->ep);
    loop->ep = NULL;
  }