sort_t *mutt_get_sort_func (int method)
{
  switch (method & SORT_MASK)
  {
    case SORT_RECEIVED:
      return (compare_date_received);
    case SORT_ORDER:
      return (compare_order);
    case SORT_DATE:
      return (compare_date_sent);
    case SORT_SUBJECT:
      return (compare_subject);
    case SORT_FROM:
      return (compare_from);
    case SORT_SIZE:
      return (compare_size);
    case SORT_TO:
      return (compare_to);
    case SORT_SCORE:
      return (compare_score);
    case SORT_SPAM:
      return (compare_spam);
    case SORT_LABEL:
      return (compare_label);
    default:
      return (NULL);
  }
  /* not reached */
}