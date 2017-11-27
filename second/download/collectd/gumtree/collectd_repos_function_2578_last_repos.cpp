int lcc_putval(lcc_connection_t *c, const lcc_value_list_t *vl) /* {{{ */
{
  char ident_str[6 * LCC_NAME_LEN];
  char ident_esc[12 * LCC_NAME_LEN];
  char command[1024] = "";
  lcc_response_t res;
  int status;

  if ((c == NULL) || (vl == NULL) || (vl->values_len < 1) ||
      (vl->values == NULL) || (vl->values_types == NULL)) {
    lcc_set_errno(c, EINVAL);
    return -1;
  }

  status = lcc_identifier_to_string(c, ident_str, sizeof(ident_str),
                                    &vl->identifier);
  if (status != 0)
    return status;

  SSTRCATF(command, "PUTVAL %s",
           lcc_strescape(ident_esc, ident_str, sizeof(ident_esc)));

  if (vl->interval > 0.0)
    SSTRCATF(command, " interval=%.3f", vl->interval);

  if (vl->time > 0.0)
    SSTRCATF(command, " %.3f", vl->time);
  else
    SSTRCAT(command, " N");

  for (size_t i = 0; i < vl->values_len; i++) {
    if (vl->values_types[i] == LCC_TYPE_COUNTER)
      SSTRCATF(command, ":%" PRIu64, vl->values[i].counter);
    else if (vl->values_types[i] == LCC_TYPE_GAUGE) {
      if (isnan(vl->values[i].gauge))
        SSTRCATF(command, ":U");
      else
        SSTRCATF(command, ":%g", vl->values[i].gauge);
    } else if (vl->values_types[i] == LCC_TYPE_DERIVE)
      SSTRCATF(command, ":%" PRIu64, vl->values[i].derive);
    else if (vl->values_types[i] == LCC_TYPE_ABSOLUTE)
      SSTRCATF(command, ":%" PRIu64, vl->values[i].absolute);

  } /* for (i = 0; i < vl->values_len; i++) */

  status = lcc_sendreceive(c, command, &res);
  if (status != 0)
    return status;

  if (res.status != 0) {
    LCC_SET_ERRSTR(c, "Server error: %s", res.message);
    lcc_response_free(&res);
    return -1;
  }

  lcc_response_free(&res);
  return 0;
}