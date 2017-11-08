void Curl_pgrsStartNow(struct SessionHandle *data)
{
  data->progress.speeder_c = 0; /* reset the progress meter display */
  data->progress.start = Curl_tvnow();
  /* clear all bits except HIDE and HEADERS_OUT */
  data->progress.flags &= PGRS_HIDE|PGRS_HEADERS_OUT;
}