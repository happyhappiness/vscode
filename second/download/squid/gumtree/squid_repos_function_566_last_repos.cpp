int
comm_open(int sock_type,
          int proto,
          Ip::Address &addr,
          int flags,
          const char *note)
{
    return comm_openex(sock_type, proto, addr, flags, note);
}