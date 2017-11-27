int lcc_identifier_compare(const void *a, /* {{{ */
                           const void *b) {
  const lcc_identifier_t *i0 = a;
  const lcc_identifier_t *i1 = b;
  int status;

  if ((i0 == NULL) && (i1 == NULL))
    return 0;
  else if (i0 == NULL)
    return -1;
  else if (i1 == NULL)
    return 1;

#define CMP_FIELD(f)                                                           \
  do {                                                                         \
    status = strcmp(i0->f, i1->f);                                             \
    if (status != 0)                                                           \
      return status;                                                           \
  } while (0);

  CMP_FIELD(host);
  CMP_FIELD(plugin);
  CMP_FIELD(plugin_instance);
  CMP_FIELD(type);
  CMP_FIELD(type_instance);

#undef CMP_FIELD

  return 0;
}