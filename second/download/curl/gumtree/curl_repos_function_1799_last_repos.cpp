static int hostmatch(char *hostname, char *pattern)
{
  const char *pattern_label_end, *pattern_wildcard, *hostname_label_end;
  int wildcard_enabled;
  size_t prefixlen, suffixlen;
  struct in_addr ignored;
#ifdef ENABLE_IPV6
  struct sockaddr_in6 si6;
#endif

  /* normalize pattern and hostname by stripping off trailing dots */
  size_t len = strlen(hostname);
  if(hostname[len-1]=='.')
    hostname[len-1] = 0;
  len = strlen(pattern);
  if(pattern[len-1]=='.')
    pattern[len-1] = 0;

  pattern_wildcard = strchr(pattern, '*');
  if(pattern_wildcard == NULL)
    return strcasecompare(pattern, hostname) ?
      CURL_HOST_MATCH : CURL_HOST_NOMATCH;

  /* detect IP address as hostname and fail the match if so */
  if(Curl_inet_pton(AF_INET, hostname, &ignored) > 0)
    return CURL_HOST_NOMATCH;
#ifdef ENABLE_IPV6
  if(Curl_inet_pton(AF_INET6, hostname, &si6.sin6_addr) > 0)
    return CURL_HOST_NOMATCH;
#endif

  /* We require at least 2 dots in pattern to avoid too wide wildcard
     match. */
  wildcard_enabled = 1;
  pattern_label_end = strchr(pattern, '.');
  if(pattern_label_end == NULL || strchr(pattern_label_end + 1, '.') == NULL ||
     pattern_wildcard > pattern_label_end ||
     strncasecompare(pattern, "xn--", 4)) {
    wildcard_enabled = 0;
  }
  if(!wildcard_enabled)
    return strcasecompare(pattern, hostname) ?
      CURL_HOST_MATCH : CURL_HOST_NOMATCH;

  hostname_label_end = strchr(hostname, '.');
  if(hostname_label_end == NULL ||
     !strcasecompare(pattern_label_end, hostname_label_end))
    return CURL_HOST_NOMATCH;

  /* The wildcard must match at least one character, so the left-most
     label of the hostname is at least as large as the left-most label
     of the pattern. */
  if(hostname_label_end - hostname < pattern_label_end - pattern)
    return CURL_HOST_NOMATCH;

  prefixlen = pattern_wildcard - pattern;
  suffixlen = pattern_label_end - (pattern_wildcard + 1);
  return strncasecompare(pattern, hostname, prefixlen) &&
    strncasecompare(pattern_wildcard + 1, hostname_label_end - suffixlen,
                    suffixlen) ?
    CURL_HOST_MATCH : CURL_HOST_NOMATCH;
}