LIST *mutt_add_list (LIST *head, const char *data)
{
  size_t len = mutt_strlen (data);

  return mutt_add_list_n (head, data, len ? len + 1 : 0);
}