static int lu_copy_ident_to_match(identifier_match_t *match, /* {{{ */
                                  lookup_identifier_t const *ident,
                                  unsigned int group_by) {
  memset(match, 0, sizeof(*match));

  match->group_by = group_by;

#define COPY_FIELD(field)                                                      \
  do {                                                                         \
    int status = lu_copy_ident_to_match_part(&match->field, ident->field);     \
    if (status != 0)                                                           \
      return (status);                                                         \
  } while (0)

  COPY_FIELD(host);
  COPY_FIELD(plugin);
  COPY_FIELD(plugin_instance);
  COPY_FIELD(type);
  COPY_FIELD(type_instance);

#undef COPY_FIELD

  return (0);
}