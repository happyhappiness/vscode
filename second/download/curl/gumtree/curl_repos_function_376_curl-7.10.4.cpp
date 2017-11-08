int main(int argc, char **argv)
{
  struct CookieInfo *c=NULL;
  if(argc>1) {
    c = Curl_cookie_init(argv[1], c);
    Curl_cookie_add(c, TRUE, "PERSONALIZE=none;expires=Monday, 13-Jun-1988 03:04:55 GMT; domain=.fidelity.com; path=/ftgw; secure");
    Curl_cookie_add(c, TRUE, "foobar=yes; domain=.haxx.se; path=/looser;");
    c = Curl_cookie_init(argv[1], c);

    Curl_cookie_output(c);
    Curl_cookie_cleanup(c);
    return 0;
  }
  return 1;
}