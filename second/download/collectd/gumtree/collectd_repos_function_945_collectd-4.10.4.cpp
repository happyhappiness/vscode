static int mv_config_add_satisfy (mv_match_t *m, /* {{{ */
    oconfig_item_t *ci)
{
  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    ERROR ("`value' match: `%s' needs exactly one string argument.",
        ci->key);
    return (-1);
  }

  if (strcasecmp ("All", ci->values[0].value.string) == 0)
    m->satisfy = SATISFY_ALL;
  else if (strcasecmp ("Any", ci->values[0].value.string) == 0)
    m->satisfy = SATISFY_ANY;
  else
  {
    ERROR ("`value' match: Passing `%s' to the `%s' option is invalid. "
        "The argument must either be `All' or `Any'.",
        ci->values[0].value.string, ci->key);
    return (-1);
  }

  return (0);
}