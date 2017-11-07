void imap_add_keywords (char* s, HEADER* h, LIST* mailbox_flags, size_t slen)
{
  LIST *keywords;

  if (!mailbox_flags || !HEADER_DATA(h) || !HEADER_DATA(h)->keywords)
    return;

  keywords = HEADER_DATA(h)->keywords->next;

  while (keywords)
  {
    if (msg_has_flag (mailbox_flags, keywords->data))
    {
      strncat (s, keywords->data, slen);
      strncat (s, " ", slen);
    }
    keywords = keywords->next;
  }
}