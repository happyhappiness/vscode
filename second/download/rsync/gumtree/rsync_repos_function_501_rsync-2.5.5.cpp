static const char *const
getTableTranslationDomain(const struct poptOption *table)
{
  const struct poptOption *opt;

  for(opt = table;
      opt->longName || opt->shortName || opt->arg;
      opt++) {
    if(opt->argInfo == POPT_ARG_INTL_DOMAIN)
      return opt->arg;
  }

  return NULL;
}