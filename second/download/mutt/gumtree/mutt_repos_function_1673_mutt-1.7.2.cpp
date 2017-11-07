static int parse_unattachments (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  char op, *p;
  LIST **listp;

  mutt_extract_token(buf, s, 0);
  if (!buf->data || *buf->data == '\0') {
    strfcpy(err->data, _("unattachments: no disposition"), err->dsize);
    return -1;
  }

  p = buf->data;
  op = *p++;
  if (op != '+' && op != '-') {
    op = '+';
    p--;
  }
  if (!ascii_strncasecmp(p, "attachment", strlen(p))) {
    if (op == '+')
      listp = &AttachAllow;
    else
      listp = &AttachExclude;
  }
  else if (!ascii_strncasecmp(p, "inline", strlen(p))) {
    if (op == '+')
      listp = &InlineAllow;
    else
      listp = &InlineExclude;
  }
  else {
    strfcpy(err->data, _("unattachments: invalid disposition"), err->dsize);
    return -1;
  }

  return parse_unattach_list(buf, s, listp, err);
}