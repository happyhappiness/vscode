static int cf_ci_append_children(oconfig_item_t *dst, oconfig_item_t *src) {
  oconfig_item_t *temp;

  if ((src == NULL) || (src->children_num == 0))
    return 0;

  temp =
      realloc(dst->children,
              sizeof(oconfig_item_t) * (dst->children_num + src->children_num));
  if (temp == NULL) {
    ERROR("configfile: realloc failed.");
    return -1;
  }
  dst->children = temp;

  memcpy(dst->children + dst->children_num, src->children,
         sizeof(oconfig_item_t) * src->children_num);
  dst->children_num += src->children_num;

  return 0;
}