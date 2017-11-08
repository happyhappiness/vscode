static CURLcode easy_events(CURLM *multi)
{
  struct events evs= {2, FALSE, 0, NULL, 0};

  /* if running event-based, do some further multi inits */
  events_setup(multi, &evs);

  return wait_or_timeout(multi, &evs);
}