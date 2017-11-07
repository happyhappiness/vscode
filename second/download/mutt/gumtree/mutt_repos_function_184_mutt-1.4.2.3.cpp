static void delete_hook (HOOK *h)
{
  FREE (&h->command);
  FREE (&h->rx.pattern);
  if (h->rx.rx)
  {
    regfree (h->rx.rx);
  }
  mutt_pattern_free (&h->pattern);
  FREE (&h);
}