static int nut_shutdown (void)
{
  nut_ups_t *this;
  nut_ups_t *next;

  this = upslist_head;
  while (this != NULL)
  {
    next = this->next;
    free_nut_ups_t (this);
    this = next;
  }

  return (0);
}