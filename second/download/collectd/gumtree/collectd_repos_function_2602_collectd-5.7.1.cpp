static int notify_systemd(void) {
  int fd;
  const char *notifysocket;
  struct sockaddr_un su = {0};
  size_t su_size;
  char buffer[] = "READY=1\n";

  notifysocket = getenv("NOTIFY_SOCKET");
  if (notifysocket == NULL)
    return 0;

  if ((strlen(notifysocket) < 2) ||
      ((notifysocket[0] != '@') && (notifysocket[0] != '/'))) {
    ERROR("invalid notification socket NOTIFY_SOCKET=\"%s\": path must be "
          "absolute",
          notifysocket);
    return 0;
  }
  NOTICE("Systemd detected, trying to signal readyness.");

  unsetenv("NOTIFY_SOCKET");

#if defined(SOCK_CLOEXEC)
  fd = socket(AF_UNIX, SOCK_DGRAM | SOCK_CLOEXEC, /* protocol = */ 0);
#else
  fd = socket(AF_UNIX, SOCK_DGRAM, /* protocol = */ 0);
#endif
  if (fd < 0) {
    char errbuf[1024];
    ERROR("creating UNIX socket failed: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return 0;
  }

  su.sun_family = AF_UNIX;
  if (notifysocket[0] != '@') {
    /* regular UNIX socket */
    sstrncpy(su.sun_path, notifysocket, sizeof(su.sun_path));
    su_size = sizeof(su);
  } else {
    /* Linux abstract namespace socket: specify address as "\0foo", i.e.
     * start with a null byte. Since null bytes have no special meaning in
     * that case, we have to set su_size correctly to cover only the bytes
     * that are part of the address. */
    sstrncpy(su.sun_path, notifysocket, sizeof(su.sun_path));
    su.sun_path[0] = 0;
    su_size = sizeof(sa_family_t) + strlen(notifysocket);
    if (su_size > sizeof(su))
      su_size = sizeof(su);
  }

  if (sendto(fd, buffer, strlen(buffer), MSG_NOSIGNAL, (void *)&su,
             (socklen_t)su_size) < 0) {
    char errbuf[1024];
    ERROR("sendto(\"%s\") failed: %s", notifysocket,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    close(fd);
    return 0;
  }

  unsetenv("NOTIFY_SOCKET");
  close(fd);
  return 1;
}