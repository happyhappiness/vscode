static int
cert_hostcheck(const char *certname, const char *hostname)
{
  char *tmp;
  const char *certdomain;
  
  if(!certname ||
     strlen(certname)<3 ||
     !hostname ||
     !strlen(hostname)) /* sanity check */
    return 0;

  if(curl_strequal(certname, hostname)) /* trivial case */
    return 1;

  certdomain = certname + 1;

  if((certname[0] != '*') || (certdomain[0] != '.'))
    return 0; /* not a wildcard certificate, check failed */
  
  if(!strchr(certdomain+1, '.'))
    return 0; /* the certificate must have at least another dot in its name */

  /* find 'certdomain' within 'hostname' */
  tmp = strstr(hostname, certdomain);
  if(tmp) {
    /* ok the certname's domain matches the hostname, let's check that it's a
       tail-match */
    if(curl_strequal(tmp, certdomain))
      /* looks like a match. Just check we havent swallowed a '.' */
      return tmp == strchr(hostname, '.');
    else
      return 0;
  }
  return 0;
}