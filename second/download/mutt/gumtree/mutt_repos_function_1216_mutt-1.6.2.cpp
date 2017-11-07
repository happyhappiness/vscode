void mutt_update_encoding (BODY *a)
{
  CONTENT *info;
  char chsbuff[STRING];

  /* override noconv when it's us-ascii */
  if (mutt_is_us_ascii (mutt_get_body_charset (chsbuff, sizeof (chsbuff), a)))
    a->noconv = 0;

  if (!a->force_charset && !a->noconv)
    mutt_delete_parameter ("charset", &a->parameter);

  if ((info = mutt_get_content_info (a->filename, a)) == NULL)
    return;

  mutt_set_encoding (a, info);
  mutt_stamp_attachment(a);

  FREE (&a->content);
  a->content = info;

}