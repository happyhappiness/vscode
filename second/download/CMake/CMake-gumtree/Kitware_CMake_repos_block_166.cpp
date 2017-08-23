{
  return snprintf(buffer, size, "GnuTLS/%s", gnutls_check_version(NULL));
}