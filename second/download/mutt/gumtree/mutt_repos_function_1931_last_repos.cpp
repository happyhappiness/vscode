static char *
internal_function
plural_lookup (domain, n, translation, translation_len)
     struct loaded_l10nfile *domain;
     unsigned long int n;
     const char *translation;
     size_t translation_len;
{
  struct loaded_domain *domaindata = (struct loaded_domain *) domain->data;
  unsigned long int index;
  const char *p;

  index = plural_eval (domaindata->plural, n);
  if (index >= domaindata->nplurals)
    /* This should never happen.  It means the plural expression and the
       given maximum value do not match.  */
    index = 0;

  /* Skip INDEX strings at TRANSLATION.  */
  p = translation;
  while (index-- > 0)
    {
#ifdef _LIBC
      p = __rawmemchr (p, '\0');
#else
      p = strchr (p, '\0');
#endif
      /* And skip over the NUL byte.  */
      p++;

      if (p >= translation + translation_len)
	/* This should never happen.  It means the plural expression
	   evaluated to a value larger than the number of variants
	   available for MSGID1.  */
	return (char *) translation;
    }
  return (char *) p;
}