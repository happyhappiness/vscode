static int memcached_connect_unix (memcached_t *st)
{
  struct sockaddr_un serv_addr;
  int fd;

  memset (&serv_addr, 0, sizeof (serv_addr));
  serv_addr.sun_family = AF_UNIX;
  sstrncpy (serv_addr.sun_path, st->socket,
      sizeof (serv_addr.sun_path));

  /* create our socket descriptor */
  fd = socket (AF_UNIX, SOCK_STREAM, 0);
  if (fd < 0)
  {
    char errbuf[1024];
    ERROR ("memcached plugin: memcached_connect_unix: socket(2) failed: %s",
        sstrerror (errno, errbuf, sizeof (errbuf)));
    return (-1);
  }

  /* connect to the memcached daemon */
  int status = connect (fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
  if (status != 0)
  {
      shutdown (fd, SHUT_RDWR);
      close (fd);
      fd = -1;
  }

  return (fd);
}