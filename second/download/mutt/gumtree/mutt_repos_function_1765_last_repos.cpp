static int parse_spam_list (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  BUFFER templ;

  mutt_buffer_init (&templ);

  /* Insist on at least one parameter */
  if (!MoreArgs(s))
  {
    if (data == MUTT_SPAM)
      strfcpy(err->data, _("spam: no matching pattern"), err->dsize);
    else
      strfcpy(err->data, _("nospam: no matching pattern"), err->dsize);
    return -1;
  }

  /* Extract the first token, a regexp */
  mutt_extract_token (buf, s, 0);

  /* data should be either MUTT_SPAM or MUTT_NOSPAM. MUTT_SPAM is for spam commands. */
  if (data == MUTT_SPAM)
  {
    /* If there's a second parameter, it's a template for the spam tag. */
    if (MoreArgs(s))
    {
      mutt_extract_token (&templ, s, 0);

      /* Add to the spam list. */
      if (add_to_replace_list (&SpamList, buf->data, templ.data, err) != 0) {
	  FREE(&templ.data);
          return -1;
      }
      FREE(&templ.data);
    }

    /* If not, try to remove from the nospam list. */
    else
    {
      mutt_remove_from_rx_list(&NoSpamList, buf->data);
    }

    return 0;
  }

  /* MUTT_NOSPAM is for nospam commands. */
  else if (data == MUTT_NOSPAM)
  {
    /* nospam only ever has one parameter. */

    /* "*" is a special case. */
    if (!mutt_strcmp(buf->data, "*"))
    {
      mutt_free_replace_list (&SpamList);
      mutt_free_rx_list (&NoSpamList);
      return 0;
    }

    /* If it's on the spam list, just remove it. */
    if (remove_from_replace_list(&SpamList, buf->data) != 0)
      return 0;

    /* Otherwise, add it to the nospam list. */
    if (mutt_add_to_rx_list (&NoSpamList, buf->data, REG_ICASE, err) != 0)
      return -1;

    return 0;
  }

  /* This should not happen. */
  strfcpy(err->data, "This is no good at all.", err->dsize);
  return -1;
}