static int cb_qsort_sbe (const void *a, const void *b)
{
  const SBENTRY *sbe1 = *(const SBENTRY **) a;
  const SBENTRY *sbe2 = *(const SBENTRY **) b;
  BUFFY *b1 = sbe1->buffy;
  BUFFY *b2 = sbe2->buffy;

  int result = 0;

  switch ((SidebarSortMethod & SORT_MASK))
  {
    case SORT_COUNT:
      result = (b2->msg_count - b1->msg_count);
      break;
    case SORT_UNREAD:
      result = (b2->msg_unread - b1->msg_unread);
      break;
    case SORT_FLAGGED:
      result = (b2->msg_flagged - b1->msg_flagged);
      break;
    case SORT_PATH:
      result = mutt_strcasecmp (b1->path, b2->path);
      break;
  }

  if (SidebarSortMethod & SORT_REVERSE)
    result = -result;

  return result;
}