int Curl_cert_hostcheck(const char *match_pattern, const char *hostname)
{
  char *matchp;
  char *hostp;
  int res = 0;
  if(!match_pattern || !*match_pattern ||
      !hostname || !*hostname) /* sanity check */
    ;
  else {
    matchp = strdup(match_pattern);
    if(matchp) {
      hostp = strdup(hostname);
      if(hostp) {
        if(hostmatch(hostp, matchp) == CURL_HOST_MATCH)
          res = 1;
        free(hostp);
      }
      free(matchp);
    }
  }

  return res;
}