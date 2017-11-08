void Curl_pgrsDone(struct connectdata *conn)
{
  struct SessionHandle *data = conn->data;
  data->progress.lastshow=0;
  Curl_pgrsUpdate(conn); /* the final (forced) update */

  data->progress.speeder_c = 0; /* reset the progress meter display */
}