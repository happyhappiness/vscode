static int parse_attachments (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  char op, *category;
  LIST **listp;

  mutt_extract_token(buf, s, 0);
  if (!buf->data || *buf->data == '\0') {
    strfcpy(err->data, _("attachments: no disposition"), err->dsize);
    return -1;
  }

  category = buf->data;
  op = *category++;

  if (op == '?') {
    mutt_endwin (NULL);
    fflush (stdout);
    printf("\nCurrent attachments settings:\n\n");
    print_attach_list(AttachAllow,   '+', "A");
    print_attach_list(AttachExclude, '-', "A");
    print_attach_list(InlineAllow,   '+', "I");
    print_attach_list(InlineExclude, '-', "I");
    set_option (OPTFORCEREDRAWINDEX);
    set_option (OPTFORCEREDRAWPAGER);
    mutt_any_key_to_continue (NULL);
    return 0;
  }

  if (op != '+' && op != '-') {
    op = '+';
    category--;
  }
  if (!ascii_strncasecmp(category, "attachment", strlen(category))) {
    if (op == '+')
      listp = &AttachAllow;
    else
      listp = &AttachExclude;
  }
  else if (!ascii_strncasecmp(category, "inline", strlen(category))) {
    if (op == '+')
      listp = &InlineAllow;
    else
      listp = &InlineExclude;
  }
  else {
    strfcpy(err->data, _("attachments: invalid disposition"), err->dsize);
    return -1;
  }

  return parse_attach_list(buf, s, listp, err);
}