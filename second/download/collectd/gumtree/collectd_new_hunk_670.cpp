      result = status;
      break;
    }
    /* else: cmd_parse_option did not find an option; treat this as a
     * value list. */

    vl.values_len = ds->ds_num;
    vl.values = calloc(vl.values_len, sizeof(*vl.values));
    if (vl.values == NULL) {
      cmd_error(CMD_ERROR, err, "malloc failed.");
      result = CMD_ERROR;
      break;
    }

    status = parse_values(argv[i], &vl, ds);
    if (status != 0) {
      cmd_error(CMD_PARSE_ERROR, err, "Parsing the values string failed.");
      result = CMD_PARSE_ERROR;
      vl.values_len = 0;
      sfree(vl.values);
      break;
    }

    tmp = realloc(ret_putval->vl,
                  (ret_putval->vl_num + 1) * sizeof(*ret_putval->vl));
    if (tmp == NULL) {
      cmd_error(CMD_ERROR, err, "realloc failed.");
      cmd_destroy_putval(ret_putval);
      result = CMD_ERROR;
      vl.values_len = 0;
      sfree(vl.values);
      break;
    }

    ret_putval->vl = tmp;
    ret_putval->vl_num++;
    memcpy(&ret_putval->vl[ret_putval->vl_num - 1], &vl, sizeof(vl));

    /* pointer is now owned by ret_putval->vl[] */
    vl.values_len = 0;
    vl.values = NULL;
  } /* while (*buffer != 0) */
  /* Done parsing the options. */

  if (result != CMD_OK)
    cmd_destroy_putval(ret_putval);

  return (result);
} /* cmd_status_t cmd_parse_putval */

void cmd_destroy_putval(cmd_putval_t *putval) {
  if (putval == NULL)
    return;

  sfree(putval->raw_identifier);

  for (size_t i = 0; i < putval->vl_num; ++i) {
    sfree(putval->vl[i].values);
    meta_data_destroy(putval->vl[i].meta);
    putval->vl[i].meta = NULL;
  }
  sfree(putval->vl);
  putval->vl = NULL;
  putval->vl_num = 0;
