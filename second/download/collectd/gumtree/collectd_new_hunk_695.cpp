      break;
    case 'd': {
      char **tmp;
      tmp = realloc(match_ds_g, (match_ds_num_g + 1) * sizeof(char *));
      if (tmp == NULL) {
        fprintf(stderr, "realloc failed: %s\n", strerror(errno));
        return RET_UNKNOWN;
      }
      match_ds_g = tmp;
      match_ds_g[match_ds_num_g] = cn_strdup(optarg);
      if (match_ds_g[match_ds_num_g] == NULL) {
        fprintf(stderr, "cn_strdup failed: %s\n", strerror(errno));
        return RET_UNKNOWN;
      }
      match_ds_num_g++;
      break;
    }
    case 'm':
      nan_is_error_g = 1;
