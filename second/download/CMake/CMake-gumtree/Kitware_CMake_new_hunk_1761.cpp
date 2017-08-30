    else
      sub[0]='\0';

    sprintf(ptr, " SSL/%x.%x.%x%s",
            (SSLEAY_VERSION_NUMBER>>12)&0xff,
            (SSLEAY_VERSION_NUMBER>>8)&0xf,
            (SSLEAY_VERSION_NUMBER>>4)&0xf, sub);
  }
#endif
#endif
}

#endif

char *curl_version(void)
{
  static char version[200];
  char *ptr;
  long num;
  strcpy(version, LIBCURL_NAME "/" LIBCURL_VERSION );
  ptr=strchr(version, '\0');

#ifdef USE_SSLEAY
  getssl_version(ptr, &num);
  ptr=strchr(version, '\0');
#else
  (void)num; /* no compiler warning please */
#endif

#ifdef KRB4
  sprintf(ptr, " krb4");
  ptr += strlen(ptr);
#endif
#ifdef ENABLE_IPV6
  sprintf(ptr, " ipv6");
  ptr += strlen(ptr);
#endif
#ifdef HAVE_LIBZ
  sprintf(ptr, " zlib/%s", zlibVersion());
  ptr += strlen(ptr);
#endif

  return version;
}

/* data for curl_version_info */

static const char *protocols[] = {
#ifndef CURL_DISABLE_FTP
  "ftp",
#endif
#ifndef CURL_DISABLE_GOPHER
  "gopher",
#endif
#ifndef CURL_DISABLE_TELNET
  "telnet",
#endif
#ifndef CURL_DISABLE_DICT
  "dict",
#endif
#ifndef CURL_DISABLE_LDAP
  "ldap",
#endif
#ifndef CURL_DISABLE_HTTP
  "http",
#endif
#ifndef CURL_DISABLE_FILE
  "file",
#endif

#ifdef USE_SSLEAY
#ifndef CURL_DISABLE_HTTP
  "https",
#endif
#ifndef CURL_DISABLE_FTP
  "ftps",
#endif
#endif
  NULL
};

static curl_version_info_data version_info = {
  CURLVERSION_FIRST,
  LIBCURL_VERSION,
  LIBCURL_VERSION_NUM,
  OS, /* as found by configure or set by hand at build-time */
  0 /* features is 0 by default */
#ifdef ENABLE_IPV6
  | CURL_VERSION_IPV6
#endif
#ifdef KRB4
  | CURL_VERSION_KERBEROS4
#endif
#ifdef USE_SSLEAY
  | CURL_VERSION_SSL
#endif
#ifdef HAVE_LIBZ
  | CURL_VERSION_LIBZ
#endif
  ,
  NULL, /* ssl_version */
  0,    /* ssl_version_num */
  NULL, /* zlib_version */
  protocols
};

curl_version_info_data *curl_version_info(CURLversion stamp)
{
#ifdef USE_SSLEAY
  static char ssl_buffer[80];
  long num;
  getssl_version(ssl_buffer, &num);

  version_info.ssl_version = ssl_buffer;
  version_info.ssl_version_num = num;
  /* SSL stuff is left zero if undefined */
#endif

#ifdef HAVE_LIBZ
  version_info.libz_version = zlibVersion();
  /* libz left NULL if non-existing */
#endif
  (void)stamp; /* avoid compiler warnings, we don't use this */

  return &version_info;
}

/*