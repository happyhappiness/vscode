static void browser_sort (struct browser_state *state)
{
  int (*f) (const void *, const void *);

  switch (BrowserSort & SORT_MASK)
  {
    case SORT_ORDER:
      return;
    case SORT_DATE:
      f = browser_compare_date;
      break;
    case SORT_SIZE:
      f = browser_compare_size;
      break;
    case SORT_SUBJECT:
    default:
      f = browser_compare_subject;
      break;
  }
  qsort (state->entry, state->entrylen, sizeof (struct folder_file), f);
}