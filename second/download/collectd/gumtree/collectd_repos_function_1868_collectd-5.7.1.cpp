void cmd_destroy_putval(cmd_putval_t *putval) {
  if (putval == NULL)
    return;

  sfree(putval->raw_identifier);

  for (size_t i = 0; i < putval->vl_num; ++i) {
    if (i == 0) /* values is shared between all entries */
      sfree(putval->vl[i].values);
    meta_data_destroy(putval->vl[i].meta);
    putval->vl[i].meta = NULL;
  }
  sfree(putval->vl);
  putval->vl = NULL;
  putval->vl_num = 0;
}