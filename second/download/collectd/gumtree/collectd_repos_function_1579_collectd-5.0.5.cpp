static meta_entry_t *md_entry_clone (const meta_entry_t *orig) /* {{{ */
{
  meta_entry_t *copy;

  if (orig == NULL)
    return (NULL);

  copy = md_entry_alloc (orig->key);
  copy->type = orig->type;
  if (copy->type == MD_TYPE_STRING)
    copy->value.mv_string = strdup (orig->value.mv_string);
  else
    copy->value = orig->value;

  copy->next = md_entry_clone (orig->next);
  return (copy);
}