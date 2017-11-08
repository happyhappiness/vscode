void Curl_pgrsDone(struct connectdata *conn)
{
  struct SessionHandle *data = conn->data;
  if(!(data->progress.flags & PGRS_HIDE)) {
    data->progress.lastshow=0;
    Curl_pgrsUpdate(conn); /* the final (forced) update */
    if(!data->progress.callback)
      /* only output if we don't use progress callback */
      fprintf(data->set.err, "\n");
  }
}