static meta_entry_t *md_entry_clone_contents(const meta_entry_t *orig) /* {{{ */
{
  meta_entry_t *copy;

  /* WARNINGS :
   *  - we do not check that orig != NULL here. You should have done it before.
   *  - we do not set copy->next. DO NOT FORGET TO SET copy->next IN YOUR
   * FUNCTION
   */

  copy = md_entry_alloc(orig->key);
  if (copy == NULL)
    return (NULL);
  copy->type = orig->type;
  if (copy->type == MD_TYPE_STRING)
    copy->value.mv_string = strdup(orig->value.mv_string);
  else
    copy->value = orig->value;

  return (copy);
}