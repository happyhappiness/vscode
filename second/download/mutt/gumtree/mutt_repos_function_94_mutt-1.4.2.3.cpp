static int match_reference (regex_t *rx, LIST *refs)
{
  for (; refs; refs = refs->next)
    if (regexec (rx, refs->data, 0, NULL, 0) == 0)
      return 1;
  return 0;
}