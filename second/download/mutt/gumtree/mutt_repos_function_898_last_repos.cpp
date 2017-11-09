static void ssl_dprint_err_stack (void)
{
#ifdef DEBUG
  BIO *bio;
  char *buf = NULL;
  long buflen;
  char *output;

  if (! (bio = BIO_new (BIO_s_mem ())))
    return;
  ERR_print_errors (bio);
  if ((buflen = BIO_get_mem_data (bio, &buf)) > 0)
  {
    output = safe_malloc (buflen + 1);
    memcpy (output, buf, buflen);
    output[buflen] = '\0';
    dprint (1, (debugfile, "SSL error stack: %s\n", output));
    FREE (&output);
  }
  BIO_free (bio);
#endif
}