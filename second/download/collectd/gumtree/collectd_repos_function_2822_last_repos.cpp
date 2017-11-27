static meta_entry_t *md_entry_clone(const meta_entry_t *orig) /* {{{ */
{
  meta_entry_t *copy;

  if (orig == NULL)
    return NULL;

  copy = md_entry_clone_contents(orig);

  copy->next = md_entry_clone(orig->next);
  return copy;
}