static int ir_shutdown(void) {
  if (nl) {
    mnl_socket_close(nl);
    nl = NULL;
  }

  return (0);
}