static int gtls_mapped_sockerrno(void)
{
  switch(SOCKERRNO) {
  case WSAEWOULDBLOCK:
    return gtls_EAGAIN;
  case WSAEINTR:
    return gtls_EINTR;
  default:
    break;
  }
  return gtls_EIO;
}