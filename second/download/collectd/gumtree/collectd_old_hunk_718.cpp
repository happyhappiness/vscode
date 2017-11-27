    }
  }

  status = yyparse();
  if (status != 0) {
    fprintf(stderr, "yyparse returned error #%i\n", status);
    return (NULL);
  }

  c_file = NULL;

  ret = ci_root;
  ci_root = NULL;
  yyset_in((FILE *)0);

  return (ret);
} /* oconfig_item_t *oconfig_parse_fh */

oconfig_item_t *oconfig_parse_file(const char *file) {
  FILE *fh;
  oconfig_item_t *ret;

  c_file = file;

  fh = fopen(file, "r");
  if (fh == NULL) {
    fprintf(stderr, "fopen (%s) failed: %s\n", file, strerror(errno));
    return (NULL);
  }

  ret = oconfig_parse_fh(fh);
  fclose(fh);

  c_file = NULL;

  return (ret);
} /* oconfig_item_t *oconfig_parse_file */

oconfig_item_t *oconfig_clone(const oconfig_item_t *ci_orig) {
  oconfig_item_t *ci_copy;

  ci_copy = calloc(1, sizeof(*ci_copy));
  if (ci_copy == NULL) {
    fprintf(stderr, "calloc failed.\n");
    return (NULL);
  }
  ci_copy->values = NULL;
  ci_copy->parent = NULL;
  ci_copy->children = NULL;

  ci_copy->key = strdup(ci_orig->key);
  if (ci_copy->key == NULL) {
    fprintf(stderr, "strdup failed.\n");
    free(ci_copy);
    return (NULL);
  }

  if (ci_orig->values_num > 0) /* {{{ */
  {
    ci_copy->values = (oconfig_value_t *)calloc((size_t)ci_orig->values_num,
                                                sizeof(*ci_copy->values));
    if (ci_copy->values == NULL) {
      fprintf(stderr, "calloc failed.\n");
      free(ci_copy->key);
      free(ci_copy);
      return (NULL);
    }
    ci_copy->values_num = ci_orig->values_num;

    for (int i = 0; i < ci_copy->values_num; i++) {
      ci_copy->values[i].type = ci_orig->values[i].type;
      if (ci_copy->values[i].type == OCONFIG_TYPE_STRING) {
        ci_copy->values[i].value.string =
            strdup(ci_orig->values[i].value.string);
        if (ci_copy->values[i].value.string == NULL) {
          fprintf(stderr, "strdup failed.\n");
          oconfig_free(ci_copy);
          return (NULL);
        }
      } else /* ci_copy->values[i].type != OCONFIG_TYPE_STRING) */
      {
        ci_copy->values[i].value = ci_orig->values[i].value;
      }
    }
