static int cf_ci_replace_child(oconfig_item_t *dst, oconfig_item_t *src,
                               int offset) {
  oconfig_item_t *temp;

  assert(offset >= 0);
  assert(dst->children_num > offset);

  /* Free the memory used by the replaced child. Usually that's the
   * `Include "blah"' statement. */
  temp = dst->children + offset;
  for (int i = 0; i < temp->values_num; i++) {
    if (temp->values[i].type == OCONFIG_TYPE_STRING) {
      sfree(temp->values[i].value.string);
    }
  }
  sfree(temp->values);
  temp = NULL;

  /* If (src->children_num == 0) the array size is decreased. If offset
   * is _not_ the last element, (offset < (dst->children_num - 1)), then
   * we need to move the trailing elements before resizing the array. */
  if ((src->children_num == 0) && (offset < (dst->children_num - 1))) {
    int nmemb = dst->children_num - (offset + 1);
    memmove(dst->children + offset, dst->children + offset + 1,
            sizeof(oconfig_item_t) * nmemb);
  }

  /* Resize the memory containing the children to be big enough to hold
   * all children. */
  if (dst->children_num + src->children_num - 1 == 0) {
    dst->children_num = 0;
    return (0);
  }

  temp =
      realloc(dst->children, sizeof(oconfig_item_t) *
                                 (dst->children_num + src->children_num - 1));
  if (temp == NULL) {
    ERROR("configfile: realloc failed.");
    return (-1);
  }
  dst->children = temp;

  /* If there are children behind the include statement, and they have
   * not yet been moved because (src->children_num == 0), then move them
   * to the end of the list, so that the new children have room before
   * them. */
  if ((src->children_num > 0) && ((dst->children_num - (offset + 1)) > 0)) {
    int nmemb = dst->children_num - (offset + 1);
    int old_offset = offset + 1;
    int new_offset = offset + src->children_num;

    memmove(dst->children + new_offset, dst->children + old_offset,
            sizeof(oconfig_item_t) * nmemb);
  }

  /* Last but not least: If there are new children, copy them to the
   * memory reserved for them. */
  if (src->children_num > 0) {
    memcpy(dst->children + offset, src->children,
           sizeof(oconfig_item_t) * src->children_num);
  }

  /* Update the number of children. */
  dst->children_num += (src->children_num - 1);

  return (0);
}