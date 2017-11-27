static void cconn_close(struct cconn *io) {
  io->state = CSTATE_UNCONNECTED;
  if (io->asok != -1) {
    int res;
    RETRY_ON_EINTR(res, close(io->asok));
  }
  io->asok = -1;
  io->amt = 0;
  io->json_len = 0;
  sfree(io->json);
  io->json = NULL;
}