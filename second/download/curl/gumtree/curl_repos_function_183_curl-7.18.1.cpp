CURLcode
curl_easy_setopt_ccsid(CURL * curl, CURLoption tag, ...)

{
  CURLcode result;
  va_list arg;
  struct SessionHandle * data;
  char * s;
  char * cp;
  unsigned int ccsid;
  size_t len;
  curl_off_t pfsize;
  static char testwarn = 1;

  /* Warns if this procedure has not been updated when the dupstring enum
     changes.
     We (try to) do it only once: there is no need to issue several times
     the same message; but since threadsafeness is not handled here,
     this may occur (and we don't care!). */

  if (testwarn) {
    testwarn = 0;

    if ((int) STRING_LAST != (int) STRING_SSH_HOST_PUBLIC_KEY_MD5 + 1)
      curl_mfprintf(stderr,
       "*** WARNING: curl_easy_setopt_ccsid() should be reworked ***\n");
    }

  data = (struct SessionHandle *) curl;
  va_start(arg, tag);

  switch (tag) {

  case CURLOPT_CAINFO:
  case CURLOPT_CAPATH:
  case CURLOPT_COOKIE:
  case CURLOPT_COOKIEFILE:
  case CURLOPT_COOKIEJAR:
  case CURLOPT_COOKIELIST:
  case CURLOPT_CUSTOMREQUEST:
  case CURLOPT_EGDSOCKET:
  case CURLOPT_ENCODING:
  case CURLOPT_FTPPORT:
  case CURLOPT_FTP_ACCOUNT:
  case CURLOPT_FTP_ALTERNATIVE_TO_USER:
  case CURLOPT_INTERFACE:
  case CURLOPT_KEYPASSWD:
  case CURLOPT_KRBLEVEL:
  case CURLOPT_NETRC_FILE:
  case CURLOPT_PROXY:
  case CURLOPT_PROXYUSERPWD:
  case CURLOPT_RANDOM_FILE:
  case CURLOPT_RANGE:
  case CURLOPT_REFERER:
  case CURLOPT_SSH_PRIVATE_KEYFILE:
  case CURLOPT_SSH_PUBLIC_KEYFILE:
  case CURLOPT_SSLCERT:
  case CURLOPT_SSLCERTTYPE:
  case CURLOPT_SSLENGINE:
  case CURLOPT_SSLKEY:
  case CURLOPT_SSLKEYTYPE:
  case CURLOPT_SSL_CIPHER_LIST:
  case CURLOPT_URL:
  case CURLOPT_USERAGENT:
  case CURLOPT_USERPWD:
  case CURLOPT_SSH_HOST_PUBLIC_KEY_MD5:
    s = va_arg(arg, char *);
    ccsid = va_arg(arg, unsigned int);

    if (s) {
      s = dynconvert(ASCII_CCSID, s, -1, ccsid);

      if (!s) {
        result = CURLE_OUT_OF_MEMORY;
        break;
        }
      }

    result = curl_easy_setopt(curl, tag, s);

    if (s)
      free(s);

    break;

  case CURLOPT_COPYPOSTFIELDS:
    /* Special case: byte count may have been given by CURLOPT_POSTFIELDSIZE
       prior to this call. In this case, convert the given byte count and
       replace the length according to the conversion result. */
    s = va_arg(arg, char *);
    ccsid = va_arg(arg, unsigned int);

    pfsize = data->set.postfieldsize;

    if (!s || !pfsize || ccsid == NOCONV_CCSID || ccsid == ASCII_CCSID) {
      result = curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, s);
      break;
      }

    if (pfsize == -1) {
      /* Data is null-terminated. */
      s = dynconvert(ASCII_CCSID, s, -1, ccsid);

      if (!s) {
        result = CURLE_OUT_OF_MEMORY;
        break;
        }
      }
    else {
      /* Data length specified. */

      if (pfsize < 0 || pfsize > SIZE_MAX) {
        result = CURLE_OUT_OF_MEMORY;
        break;
        }

      len = pfsize;
      pfsize = len * MAX_CONV_EXPANSION;

      if (pfsize > SIZE_MAX)
        pfsize = SIZE_MAX;

      cp = malloc(pfsize);

      if (!cp) {
        result = CURLE_OUT_OF_MEMORY;
        break;
        }

      pfsize = convert(cp, pfsize, ASCII_CCSID, s, len, ccsid);

      if (pfsize < 0) {
        free(cp);
        result = CURLE_OUT_OF_MEMORY;
        break;
        }

      data->set.postfieldsize = pfsize;         /* Replace data size. */
      s = cp;
      }

    result = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, s);
    data->set.str[STRING_COPYPOSTFIELDS] = s;   /* Give to library. */
    break;

  case CURLOPT_ERRORBUFFER:                     /* This is an output buffer. */
  default:
    result = Curl_setopt(data, tag, arg);
    break;
    }

  va_end(arg);
  return result;
}