void
internal_function
_nl_unload_domain (domain)
     struct loaded_domain *domain;
{
  if (domain->plural != &germanic_plural)
    __gettext_free_exp (domain->plural);

  _nl_free_domain_conv (domain);

# ifdef _POSIX_MAPPED_FILES
  if (domain->use_mmap)
    munmap ((caddr_t) domain->data, domain->mmap_size);
  else
# endif	/* _POSIX_MAPPED_FILES */
    free ((void *) domain->data);

  free (domain);
}