static int first_mailing_list (char *buf, size_t buflen, ADDRESS *a)
{
  for (; a; a = a->next)
  {
    if (mutt_is_subscribed_list (a))
    {
      mutt_save_path (buf, buflen, a);
      return 1;
    }
  }
  return 0;
}