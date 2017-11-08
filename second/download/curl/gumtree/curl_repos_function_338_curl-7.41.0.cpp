curl_version_info_data *
curl_version_info_ccsid(CURLversion stamp, unsigned int ccsid)

{
  curl_version_info_data * p;
  char * cp;
  int n;
  int nproto;
  curl_version_info_data * id;

  /* The assertion below is possible, because although the second operand
     is an enum member, the first is a #define. In that case, the OS/400 C
     compiler seems to compare string values after substitution. */

#if CURLVERSION_NOW != CURLVERSION_FOURTH
#error curl_version_info_data structure has changed: upgrade this procedure.
#endif

  /* If caller has been compiled with a new version, error. */

  if(stamp > CURLVERSION_NOW)
    return (curl_version_info_data *) NULL;

  p = curl_version_info(stamp);

  if(!p)
    return p;

  /* Measure thread space needed. */

  n = 0;
  nproto = 0;

  if(p->protocols) {
    while(p->protocols[nproto])
      n += strlen(p->protocols[nproto++]);

    n += nproto++;
    }

  if(p->version)
    n += strlen(p->version) + 1;

  if(p->host)
    n += strlen(p->host) + 1;

  if(p->ssl_version)
    n += strlen(p->ssl_version) + 1;

  if(p->libz_version)
    n += strlen(p->libz_version) + 1;

  if(p->ares)
    n += strlen(p->ares) + 1;

  if(p->libidn)
    n += strlen(p->libidn) + 1;

  if(p->libssh_version)
    n += strlen(p->libssh_version) + 1;

  /* Allocate thread space. */

  n *= MAX_CONV_EXPANSION;

  if(nproto)
    n += nproto * sizeof(const char *);

  cp = Curl_thread_buffer(LK_VERSION_INFO_DATA, n);
  id = (curl_version_info_data *) Curl_thread_buffer(LK_VERSION_INFO,
                                                     sizeof *id);

  if(!id || !cp)
    return (curl_version_info_data *) NULL;

  /* Copy data and convert strings. */

  memcpy((char *) id, (char *) p, sizeof *p);

  if(id->protocols) {
    int i = nproto * sizeof id->protocols[0];

    id->protocols = (const char * const *) cp;
    memcpy(cp, (char *) p->protocols, i);
    cp += i;
    n -= i;

    for(i = 0; id->protocols[i]; i++)
      if(convert_version_info_string(((const char * *) id->protocols) + i,
                                      &cp, &n, ccsid))
        return (curl_version_info_data *) NULL;
    }

  if(convert_version_info_string(&id->version, &cp, &n, ccsid))
    return (curl_version_info_data *) NULL;

  if(convert_version_info_string(&id->host, &cp, &n, ccsid))
    return (curl_version_info_data *) NULL;

  if(convert_version_info_string(&id->ssl_version, &cp, &n, ccsid))
    return (curl_version_info_data *) NULL;

  if(convert_version_info_string(&id->libz_version, &cp, &n, ccsid))
    return (curl_version_info_data *) NULL;

  if(convert_version_info_string(&id->ares, &cp, &n, ccsid))
    return (curl_version_info_data *) NULL;

  if(convert_version_info_string(&id->libidn, &cp, &n, ccsid))
    return (curl_version_info_data *) NULL;

  if(convert_version_info_string(&id->libssh_version, &cp, &n, ccsid))
    return (curl_version_info_data *) NULL;

  return id;
}