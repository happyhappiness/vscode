static int fc_config_add_dir_mtime(fc_directory_conf_t *dir,
                                   oconfig_item_t *ci) {
  if ((ci->values_num != 1) || ((ci->values[0].type != OCONFIG_TYPE_STRING) &&
                                (ci->values[0].type != OCONFIG_TYPE_NUMBER))) {
    WARNING("filecount plugin: The `MTime' config option needs exactly one "
            "string or numeric argument.");
    return -1;
  }

  if (ci->values[0].type == OCONFIG_TYPE_NUMBER) {
    dir->mtime = (int64_t)ci->values[0].value.number;
    return 0;
  }

  errno = 0;
  char *endptr = NULL;
  double temp = strtod(ci->values[0].value.string, &endptr);
  if ((errno != 0) || (endptr == NULL) ||
      (endptr == ci->values[0].value.string)) {
    WARNING("filecount plugin: Converting `%s' to a number failed.",
            ci->values[0].value.string);
    return -1;
  }

  switch (*endptr) {
  case 0:
  case 's':
  case 'S':
    break;

  case 'm':
  case 'M':
    temp *= 60;
    break;

  case 'h':
  case 'H':
    temp *= 3600;
    break;

  case 'd':
  case 'D':
    temp *= 86400;
    break;

  case 'w':
  case 'W':
    temp *= 7 * 86400;
    break;

  case 'y':
  case 'Y':
    temp *= 31557600; /* == 365.25 * 86400 */
    break;

  default:
    WARNING("filecount plugin: Invalid suffix for `MTime': `%c'", *endptr);
    return -1;
  } /* switch (*endptr) */

  dir->mtime = (int64_t)temp;

  return 0;
}