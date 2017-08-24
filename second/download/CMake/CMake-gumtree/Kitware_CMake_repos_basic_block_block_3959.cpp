{
      f->fd = m->socket.fd;
      f->events = m->socket.events;
      f->revents = 0;
      /* fprintf(stderr, "poll() %d check socket %d\n", numfds, f->fd); */
      f++;
      numfds++;
    }