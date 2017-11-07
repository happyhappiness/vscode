static struct maildir *skip_duplicates (struct maildir *p, struct maildir **last)
{
  /*
   * Skip ahead to the next non-duplicate message.
   *
   * p should never reach NULL, because we couldn't have reached this point unless
   * there was a message that needed to be parsed.
   *
   * the check for p->header_parsed is likely unnecessary since the dupes will most
   * likely be at the head of the list.  but it is present for consistency with
   * the check at the top of the for() loop in maildir_delayed_parsing().
   */
  while (!p->h || p->header_parsed) {
    *last = p;
    p = p->next;
  }
  return p;
}