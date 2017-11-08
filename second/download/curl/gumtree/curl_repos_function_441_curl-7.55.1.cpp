static void reset_data(struct cb_data *data, CURL *curl)
{
  data->easy_handle = curl;
  data->response_received = 0;
  data->paused = 0;
  data->remaining_bytes = 3;
}