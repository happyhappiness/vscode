const char *Curl_idn_strerror (struct connectdata *conn, int err)
{
#ifdef HAVE_IDNA_STRERROR
  (void)conn;
  return idna_strerror((Idna_rc) err);
#else
  const char *str;
  char *buf;
  size_t max;

  curlassert(conn);

  buf = conn->syserr_buf;
  max = sizeof(conn->syserr_buf)-1;

#ifndef CURL_DISABLE_VERBOSE_STRINGS
  switch ((Idna_rc)err) {
    case IDNA_SUCCESS:
      str = "No error";
      break;
    case IDNA_STRINGPREP_ERROR:
      str = "Error in string preparation";
      break;
    case IDNA_PUNYCODE_ERROR:
      str = "Error in Punycode operation";
      break;
    case IDNA_CONTAINS_NON_LDH:
      str = "Illegal ASCII characters";
      break;
    case IDNA_CONTAINS_MINUS:
      str = "Contains minus";
      break;
    case IDNA_INVALID_LENGTH:
      str = "Invalid output length";
      break;
    case IDNA_NO_ACE_PREFIX:
      str = "No ACE prefix (\"xn--\")";
      break;
    case IDNA_ROUNDTRIP_VERIFY_ERROR:
      str = "Roundtrip verify error";
      break;
    case IDNA_CONTAINS_ACE_PREFIX:
      str = "Already have ACE prefix (\"xn--\")";
      break;
    case IDNA_ICONV_ERROR:
      str = "Locale conversion failed";
      break;
    case IDNA_MALLOC_ERROR:
      str = "Allocation failed";
      break;
    case IDNA_DLOPEN_ERROR:
      str = "dlopen() error";
      break;
    default:
      snprintf(buf, max, "error %d", (int)err);
      str = NULL;
      break;
  }
#else
  if ((Idna_rc)err == IDNA_SUCCESS)
    str = "No error";
  else
    str = "error";
#endif
  if (str)
    strncpy(buf, str, max);
  buf[max] = '\0';
  return (buf);
#endif
}