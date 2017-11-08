static void ftp_respinit(struct connectdata *conn)
{
  struct FTP *ftp = conn->proto.ftp;
  ftp->nread_resp = 0;
  ftp->linestart_resp = conn->data->state.buffer;
}