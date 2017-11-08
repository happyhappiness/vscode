void Curl_pgrsStartNow(struct SessionHandle *data)
{
  data->progress.speeder_c = 0; /* reset the progress meter display */
  data->progress.start = Curl_tvnow();
}