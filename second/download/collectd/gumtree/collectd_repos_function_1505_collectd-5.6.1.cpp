static int format_json_meta (yajl_gen g, notification_meta_t *meta) /* {{{ */
{
  if (meta == NULL)
    return 0;

  JSON_ADD (g, meta->name);
  switch (meta->type)
  {
    case NM_TYPE_STRING:
      JSON_ADD (g, meta->nm_value.nm_string);
      break;
    case NM_TYPE_SIGNED_INT:
      JSON_ADDF (g, "%"PRIi64, meta->nm_value.nm_signed_int);
      break;
    case NM_TYPE_UNSIGNED_INT:
      JSON_ADDF (g, "%"PRIu64, meta->nm_value.nm_unsigned_int);
      break;
    case NM_TYPE_DOUBLE:
      JSON_ADDF (g, JSON_GAUGE_FORMAT, meta->nm_value.nm_double);
      break;
    case NM_TYPE_BOOLEAN:
      JSON_ADD (g, meta->nm_value.nm_boolean ? "true" : "false");
      break;
    default:
      ERROR ("format_json_meta: unknown meta data type %d (name \"%s\")", meta->type, meta->name);
      yajl_gen_null (g);
  }

  return format_json_meta (g, meta->next);
}