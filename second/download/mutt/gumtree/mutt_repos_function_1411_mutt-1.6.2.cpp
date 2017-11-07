static void
shift_class_colors (struct q_class_t *QuoteList, struct q_class_t *new_class,
		      int index, int *q_level)
{
  struct q_class_t * q_list;

  q_list = QuoteList;
  new_class->index = -1;

  while (q_list)
  {
    if (q_list->index >= index)
    {
      q_list->index++;
      q_list->color = ColorQuote[q_list->index % ColorQuoteUsed];
    }
    if (q_list->down)
      q_list = q_list->down;
    else if (q_list->next)
      q_list = q_list->next;
    else
    {
      while (!q_list->next)
      {
	q_list = q_list->up;
	if (q_list == NULL)
	  break;
      }
      if (q_list)
	q_list = q_list->next;
    }
  }

  new_class->index = index;
  new_class->color = ColorQuote[index % ColorQuoteUsed];
  (*q_level)++;
}