static void compound_results(struct ResolverResults *res,
                             Curl_addrinfo *ai)
{
  Curl_addrinfo *ai_tail;
  if(!ai)
    return;
  ai_tail = ai;

  while(ai_tail->ai_next)
    ai_tail = ai_tail->ai_next;

  /* Add the new results to the list of old results. */
  ai_tail->ai_next = res->temp_ai;
  res->temp_ai = ai;
}