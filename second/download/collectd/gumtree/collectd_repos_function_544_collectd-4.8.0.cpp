static int fc_config_add_dir_size (fc_directory_conf_t *dir,
    oconfig_item_t *ci)
{
  char *endptr;
  double temp;

  if ((ci->values_num != 1)
      || ((ci->values[0].type != OCONFIG_TYPE_STRING)
        && (ci->values[0].type != OCONFIG_TYPE_NUMBER)))
  {
    WARNING ("filecount plugin: The `Size' config option needs exactly one "
        "string or numeric argument.");
    return (-1);
  }

  if (ci->values[0].type == OCONFIG_TYPE_NUMBER)
  {
    dir->size = (int64_t) ci->values[0].value.number;
    return (0);
  }

  errno = 0;
  endptr = NULL;
  temp = strtod (ci->values[0].value.string, &endptr);
  if ((errno != 0) || (endptr == NULL)
      || (endptr == ci->values[0].value.string))
  {
    WARNING ("filecount plugin: Converting `%s' to a number failed.",
        ci->values[0].value.string);
    return (-1);
  }

  switch (*endptr)
  {
    case 0:
    case 'b':
    case 'B':
      break;

    case 'k':
    case 'K':
      temp *= 1000.0;
      break;

    case 'm':
    case 'M':
      temp *= 1000.0 * 1000.0;
      break;

    case 'g':
    case 'G':
      temp *= 1000.0 * 1000.0 * 1000.0;
      break;

    case 't':
    case 'T':
      temp *= 1000.0 * 1000.0 * 1000.0 * 1000.0;
      break;

    case 'p':
    case 'P':
      temp *= 1000.0 * 1000.0 * 1000.0 * 1000.0 * 1000.0;
      break;

    default:
      WARNING ("filecount plugin: Invalid suffix for `Size': `%c'", *endptr);
      return (-1);
  } /* switch (*endptr) */

  dir->size = (int64_t) temp;

  return (0);
}