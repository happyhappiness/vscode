int Curl_pgrsDone(struct connectdata *conn)
{
  int rc;
  struct Curl_easy *data = conn->data;
  data->progress.lastshow = 0;
  rc = Curl_pgrsUpdate(conn); /* the final (forced) update */
  if(rc)
    return rc;

  if(!(data->progress.flags & PGRS_HIDE) &&
     !data->progress.callback)
    /* only output if we don't use a progress callback and we're not
     * hidden */
    fprintf(data->set.err, "\n");

  data->progress.speeder_c = 0; /* reset the progress meter display */
  return 0;
}