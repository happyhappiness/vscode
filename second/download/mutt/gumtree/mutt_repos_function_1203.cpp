static int compare_threads (const void *a, const void *b)
{
  static sort_t *sort_func = NULL;

  if (a && b)
    return ((*sort_func) (&(*((THREAD **) a))->sort_key,
			  &(*((THREAD **) b))->sort_key));
  /* a hack to let us reset sort_func even though we can't
   * have extra arguments because of qsort
   */
  else
  {
    sort_func = mutt_get_sort_func (Sort);
    return (sort_func ? 1 : 0);
  }
}