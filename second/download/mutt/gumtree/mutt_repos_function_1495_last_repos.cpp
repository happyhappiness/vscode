static void
new_class_color (struct q_class_t *class, int *q_level)
{
  class->index = (*q_level)++;
  class->color = ColorQuote[class->index % ColorQuoteUsed];
}