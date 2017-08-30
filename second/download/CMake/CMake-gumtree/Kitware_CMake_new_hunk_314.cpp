  return strdup(*beg? "TRUE": "FALSE");

}



static const char *octet2str(const char *beg, const char *end)

{

  size_t n = end - beg;

  char *buf = NULL;



  /* Convert an ASN.1 octet string to a printable string.

     Return the dynamically allocated string, or NULL if an error occurs. */



  if(n <= (CURL_SIZE_T_MAX - 1) / 3) {

    buf = malloc(3 * n + 1);

    if(buf)

      for(n = 0; beg < end; n += 3)

        snprintf(buf + n, 4, "%02x:", *(const unsigned char *) beg++);

  }

  return buf;

}



static const char *bit2str(const char *beg, const char *end)

{

  /* Convert an ASN.1 bit string to a printable string.

     Return the dynamically allocated string, or NULL if an error occurs. */

