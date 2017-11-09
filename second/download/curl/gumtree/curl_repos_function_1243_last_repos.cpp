void Curl_pgrsStartNow(struct Curl_easy *data)
{
  data->progress.speeder_c = 0; /* reset the progress meter display */
  data->progress.start = Curl_tvnow();
  data->progress.is_t_startransfer_set = false;
  data->progress.ul_limit_start.tv_sec = 0;
  data->progress.ul_limit_start.tv_usec = 0;
  data->progress.dl_limit_start.tv_sec = 0;
  data->progress.dl_limit_start.tv_usec = 0;
  /* clear all bits except HIDE and HEADERS_OUT */
  data->progress.flags &= PGRS_HIDE|PGRS_HEADERS_OUT;
}