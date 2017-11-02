const char *
Curl_gsk_strerror_a(int gsk_return_value)

{
  return set_thread_string(LK_GSK_ERROR, gsk_strerror(gsk_return_value));
}