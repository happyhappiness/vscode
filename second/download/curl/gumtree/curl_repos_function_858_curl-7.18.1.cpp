static void ftp_respinit(struct connectdata *conn)
{
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  ftpc->nread_resp = 0;
  ftpc->linestart_resp = conn->data->state.buffer;
}