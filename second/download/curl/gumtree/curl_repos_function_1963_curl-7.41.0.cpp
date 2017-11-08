static CURLcode sasl_create_external_message(struct SessionHandle *data,
                                             const char *user, char **outptr,
                                             size_t *outlen)
{
  /* This is the same formatting as the login message. */
  return sasl_create_login_message(data, user, outptr, outlen);
}