{
    Curl_cookie_freelist(cookies->cookies);
    cookies->cookies = NULL;
    cookies->numcookies = 0;
  }