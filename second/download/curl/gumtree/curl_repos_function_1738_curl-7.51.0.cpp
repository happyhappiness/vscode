static ssize_t
utf8asn1str(char * * to, int type, const char * from, const char * end)
{
  size_t inlength = end - from;
  int size = 1;
  size_t outlength;
  int charsize;
  unsigned int wc;
  char * buf;

  /* Perform a lazy conversion from an ASN.1 typed string to UTF8. Allocate the
     destination buffer dynamically. The allocation size will normally be too
     large: this is to avoid buffer overflows.
     Terminate the string with a nul byte and return the converted
     string length. */

  *to = (char *) NULL;
  switch (type) {
  case CURL_ASN1_BMP_STRING:
    size = 2;
    break;
  case CURL_ASN1_UNIVERSAL_STRING:
    size = 4;
    break;
  case CURL_ASN1_NUMERIC_STRING:
  case CURL_ASN1_PRINTABLE_STRING:
  case CURL_ASN1_TELETEX_STRING:
  case CURL_ASN1_IA5_STRING:
  case CURL_ASN1_VISIBLE_STRING:
  case CURL_ASN1_UTF8_STRING:
    break;
  default:
    return -1;  /* Conversion not supported. */
  }

  if(inlength % size)
    return -1;  /* Length inconsistent with character size. */
  buf = malloc(4 * (inlength / size) + 1);
  if(!buf)
    return -1;  /* Not enough memory. */

  if(type == CURL_ASN1_UTF8_STRING) {
    /* Just copy. */
    outlength = inlength;
    if(outlength)
      memcpy(buf, from, outlength);
  }
  else {
    for(outlength = 0; from < end;) {
      wc = 0;
      switch (size) {
      case 4:
        wc = (wc << 8) | *(const unsigned char *) from++;
        wc = (wc << 8) | *(const unsigned char *) from++;
        /* fallthrough */
      case 2:
        wc = (wc << 8) | *(const unsigned char *) from++;
        /* fallthrough */
      default: /* case 1: */
        wc = (wc << 8) | *(const unsigned char *) from++;
      }
      charsize = 1;
      if(wc >= 0x00000080) {
        if(wc >= 0x00000800) {
          if(wc >= 0x00010000) {
            if(wc >= 0x00200000) {
              free(buf);
              return -1;        /* Invalid char. size for target encoding. */
            }
            buf[outlength + 3] = (char) (0x80 | (wc & 0x3F));
            wc = (wc >> 6) | 0x00010000;
            charsize++;
          }
          buf[outlength + 2] = (char) (0x80 | (wc & 0x3F));
          wc = (wc >> 6) | 0x00000800;
          charsize++;
        }
        buf[outlength + 1] = (char) (0x80 | (wc & 0x3F));
        wc = (wc >> 6) | 0x000000C0;
        charsize++;
      }
      buf[outlength] = (char) wc;
      outlength += charsize;
    }
  }
  buf[outlength] = '\0';
  *to = buf;
  return outlength;
}