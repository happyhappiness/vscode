int format_json_notification (char *buffer, size_t buffer_size, /* {{{ */
                              notification_t const *n)
{
  yajl_gen g;
  unsigned char const *out;
#if HAVE_YAJL_V2
  size_t unused_out_len;
#else
  unsigned int unused_out_len;
#endif

  if ((buffer == NULL) || (n == NULL))
    return EINVAL;

#if HAVE_YAJL_V2
  g = yajl_gen_alloc (NULL);
  if (g == NULL)
    return -1;
# if COLLECT_DEBUG
  yajl_gen_config (g, yajl_gen_beautify, 1);
  yajl_gen_config (g, yajl_gen_validate_utf8, 1);
# endif

#else /* !HAVE_YAJL_V2 */
  yajl_gen_config conf = { 0 };
# if COLLECT_DEBUG
  conf.beautify = 1;
  conf.indentString = "  ";
# endif
  g = yajl_gen_alloc (&conf, NULL);
  if (g == NULL)
    return -1;
#endif

  if (format_alert (g, n) != 0)
  {
    yajl_gen_clear (g);
    yajl_gen_free (g);
    return -1;
  }

  /* copy to output buffer */
  yajl_gen_get_buf (g, &out, &unused_out_len);
  sstrncpy (buffer, (void *) out, buffer_size);

  yajl_gen_clear (g);
  yajl_gen_free (g);
  return 0;
}