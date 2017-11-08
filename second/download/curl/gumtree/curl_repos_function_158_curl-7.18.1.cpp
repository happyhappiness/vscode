char *
Curl_ldap_err2string_a(int error)

{
  int i;
  char * cp;
  char * cp2;

  cp = ldap_err2string(error);

  if (!cp)
    return cp;

  i = strlen(cp);

  if (!(cp2 = Curl_thread_buffer(LK_LDAP_ERROR, MAX_CONV_EXPANSION * i + 1)))
    return cp2;

  i = QadrtConvertE2A(cp2, cp, MAX_CONV_EXPANSION * i, i);
  cp2[i] = '\0';
  return cp2;
}