void
internal_function
_nl_load_domain (domain_file, domainbinding)
     struct loaded_l10nfile *domain_file;
     struct binding *domainbinding;
{
  int fd;
  size_t size;
#ifdef _LIBC
  struct stat64 st;
#else
  struct stat st;
#endif
  struct mo_file_header *data = (struct mo_file_header *) -1;
  int use_mmap = 0;
  struct loaded_domain *domain;
  const char *nullentry;

  domain_file->decided = 1;
  domain_file->data = NULL;

  /* Note that it would be useless to store domainbinding in domain_file
     because domainbinding might be == NULL now but != NULL later (after
     a call to bind_textdomain_codeset).  */

  /* If the record does not represent a valid locale the FILENAME
     might be NULL.  This can happen when according to the given
     specification the locale file name is different for XPG and CEN
     syntax.  */
  if (domain_file->filename == NULL)
    return;

  /* Try to open the addressed file.  */
  fd = open (domain_file->filename, O_RDONLY | O_BINARY);
  if (fd == -1)
    return;

  /* We must know about the size of the file.  */
  if (
#ifdef _LIBC
      __builtin_expect (fstat64 (fd, &st) != 0, 0)
#else
      __builtin_expect (fstat (fd, &st) != 0, 0)
#endif
      || __builtin_expect ((size = (size_t) st.st_size) != st.st_size, 0)
      || __builtin_expect (size < sizeof (struct mo_file_header), 0))
    {
      /* Something went wrong.  */
      close (fd);
      return;
    }

#ifdef HAVE_MMAP
  /* Now we are ready to load the file.  If mmap() is available we try
     this first.  If not available or it failed we try to load it.  */
  data = (struct mo_file_header *) mmap (NULL, size, PROT_READ,
					 MAP_PRIVATE, fd, 0);

  if (__builtin_expect (data != (struct mo_file_header *) -1, 1))
    {
      /* mmap() call was successful.  */
      close (fd);
      use_mmap = 1;
    }
#endif

  /* If the data is not yet available (i.e. mmap'ed) we try to load
     it manually.  */
  if (data == (struct mo_file_header *) -1)
    {
      size_t to_read;
      char *read_ptr;

      data = (struct mo_file_header *) malloc (size);
      if (data == NULL)
	return;

      to_read = size;
      read_ptr = (char *) data;
      do
	{
	  long int nb = (long int) read (fd, read_ptr, to_read);
	  if (nb <= 0)
	    {
#ifdef EINTR
	      if (nb == -1 && errno == EINTR)
		continue;
#endif
	      close (fd);
	      return;
	    }
	  read_ptr += nb;
	  to_read -= nb;
	}
      while (to_read > 0);

      close (fd);
    }

  /* Using the magic number we can test whether it really is a message
     catalog file.  */
  if (__builtin_expect (data->magic != _MAGIC && data->magic != _MAGIC_SWAPPED,
			0))
    {
      /* The magic number is wrong: not a message catalog file.  */
#ifdef HAVE_MMAP
      if (use_mmap)
	munmap ((caddr_t) data, size);
      else
#endif
	free (data);
      return;
    }

  domain = (struct loaded_domain *) malloc (sizeof (struct loaded_domain));
  if (domain == NULL)
    return;
  domain_file->data = domain;

  domain->data = (char *) data;
  domain->use_mmap = use_mmap;
  domain->mmap_size = size;
  domain->must_swap = data->magic != _MAGIC;

  /* Fill in the information about the available tables.  */
  switch (W (domain->must_swap, data->revision))
    {
    case 0:
      domain->nstrings = W (domain->must_swap, data->nstrings);
      domain->orig_tab = (struct string_desc *)
	((char *) data + W (domain->must_swap, data->orig_tab_offset));
      domain->trans_tab = (struct string_desc *)
	((char *) data + W (domain->must_swap, data->trans_tab_offset));
      domain->hash_size = W (domain->must_swap, data->hash_tab_size);
      domain->hash_tab = (nls_uint32 *)
	((char *) data + W (domain->must_swap, data->hash_tab_offset));
      break;
    default:
      /* This is an invalid revision.  */
#ifdef HAVE_MMAP
      if (use_mmap)
	munmap ((caddr_t) data, size);
      else
#endif
	free (data);
      free (domain);
      domain_file->data = NULL;
      return;
    }

  /* Now initialize the character set converter from the character set
     the file is encoded with (found in the header entry) to the domain's
     specified character set or the locale's character set.  */
  nullentry = _nl_init_domain_conv (domain_file, domain, domainbinding);

  /* Also look for a plural specification.  */
  if (nullentry != NULL)
    {
      const char *plural;
      const char *nplurals;

      plural = strstr (nullentry, "plural=");
      nplurals = strstr (nullentry, "nplurals=");
      if (plural == NULL || nplurals == NULL)
	goto no_plural;
      else
	{
	  /* First get the number.  */
	  char *endp;
	  unsigned long int n;
	  struct parse_args args;

	  nplurals += 9;
	  while (*nplurals != '\0' && isspace ((unsigned char) *nplurals))
	    ++nplurals;
#if defined HAVE_STRTOUL || defined _LIBC
	  n = strtoul (nplurals, &endp, 10);
#else
	  for (endp = nplurals, n = 0; *endp >= '0' && *endp <= '9'; endp++)
	    n = n * 10 + (*endp - '0');
#endif
	  domain->nplurals = n;
	  if (nplurals == endp)
	    goto no_plural;

	  /* Due to the restrictions bison imposes onto the interface of the
	     scanner function we have to put the input string and the result
	     passed up from the parser into the same structure which address
	     is passed down to the parser.  */
	  plural += 7;
	  args.cp = plural;
	  if (PLURAL_PARSE (&args) != 0)
	    goto no_plural;
	  domain->plural = args.res;
	}
    }
  else
    {
      /* By default we are using the Germanic form: singular form only
         for `one', the plural form otherwise.  Yes, this is also what
         English is using since English is a Germanic language.  */
    no_plural:
      INIT_GERMANIC_PLURAL ();
      domain->plural = &germanic_plural;
      domain->nplurals = 2;
    }
}