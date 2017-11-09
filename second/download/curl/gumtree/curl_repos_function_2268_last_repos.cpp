static CURLcode easy_events(struct Curl_multi *multi)
{
  /* this struct is made static to allow it to be used after this function
     returns and curl_multi_remove_handle() is called */
  static struct events evs = {2, FALSE, 0, NULL, 0};

  /* if running event-based, do some further multi inits */
  events_setup(multi, &evs);

  return wait_or_timeout(multi, &evs);
}