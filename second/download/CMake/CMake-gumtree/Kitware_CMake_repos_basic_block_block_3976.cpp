{
    curl_slist_free_all(outcurl->change.cookielist);
    outcurl->change.cookielist = NULL;
    Curl_safefree(outcurl->state.buffer);
    Curl_safefree(outcurl->state.headerbuff);
    Curl_safefree(outcurl->change.url);
    Curl_safefree(outcurl->change.referer);
    Curl_freeset(outcurl);
    free(outcurl);
  }