void
internal_function
_nl_free_domain_conv (domain)
     struct loaded_domain *domain;
{
  if (domain->conv_tab != NULL && domain->conv_tab != (char **) -1)
    free (domain->conv_tab);

#ifdef _LIBC
  if (domain->conv != (__gconv_t) -1)
    __gconv_close (domain->conv);
#else
# if HAVE_ICONV
  if (domain->conv != (iconv_t) -1)
    iconv_close (domain->conv);
# endif
#endif
}