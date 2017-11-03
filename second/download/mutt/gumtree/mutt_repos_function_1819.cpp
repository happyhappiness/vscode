char *
internal_function
_nl_find_msg (domain_file, domainbinding, msgid, lengthp)
     struct loaded_l10nfile *domain_file;
     struct binding *domainbinding;
     const char *msgid;
     size_t *lengthp;
{
  struct loaded_domain *domain;
  size_t act;
  char *result;
  size_t resultlen;

  if (domain_file->decided == 0)
    _nl_load_domain (domain_file, domainbinding);

  if (domain_file->data == NULL)
    return NULL;

  domain = (struct loaded_domain *) domain_file->data;

  /* Locate the MSGID and its translation.  */
  if (domain->hash_size > 2 && domain->hash_tab != NULL)
    {
      /* Use the hashing table.  */
      nls_uint32 len = strlen (msgid);
      nls_uint32 hash_val = hash_string (msgid);
      nls_uint32 idx = hash_val % domain->hash_size;
      nls_uint32 incr = 1 + (hash_val % (domain->hash_size - 2));

      while (1)
	{
	  nls_uint32 nstr = W (domain->must_swap, domain->hash_tab[idx]);

	  if (nstr == 0)
	    /* Hash table entry is empty.  */
	    return NULL;

	  /* Compare msgid with the original string at index nstr-1.
	     We compare the lengths with >=, not ==, because plural entries
	     are represented by strings with an embedded NUL.  */
	  if (W (domain->must_swap, domain->orig_tab[nstr - 1].length) >= len
	      && (strcmp (msgid,
			  domain->data + W (domain->must_swap,
					    domain->orig_tab[nstr - 1].offset))
		  == 0))
	    {
	      act = nstr - 1;
	      goto found;
	    }

	  if (idx >= domain->hash_size - incr)
	    idx -= domain->hash_size - incr;
	  else
	    idx += incr;
	}
      /* NOTREACHED */
    }
  else
    {
      /* Try the default method:  binary search in the sorted array of
	 messages.  */
      size_t top, bottom;

      bottom = 0;
      top = domain->nstrings;
      while (bottom < top)
	{
	  int cmp_val;

	  act = (bottom + top) / 2;
	  cmp_val = strcmp (msgid, (domain->data
				    + W (domain->must_swap,
					 domain->orig_tab[act].offset)));
	  if (cmp_val < 0)
	    top = act;
	  else if (cmp_val > 0)
	    bottom = act + 1;
	  else
	    goto found;
	}
      /* No translation was found.  */
      return NULL;
    }

 found:
  /* The translation was found at index ACT.  If we have to convert the
     string to use a different character set, this is the time.  */
  result = ((char *) domain->data
	    + W (domain->must_swap, domain->trans_tab[act].offset));
  resultlen = W (domain->must_swap, domain->trans_tab[act].length) + 1;

#if defined _LIBC || HAVE_ICONV
  if (domain->codeset_cntr
      != (domainbinding != NULL ? domainbinding->codeset_cntr : 0))
    {
      /* The domain's codeset has changed through bind_textdomain_codeset()
	 since the message catalog was initialized or last accessed.  We
	 have to reinitialize the converter.  */
      _nl_free_domain_conv (domain);
      _nl_init_domain_conv (domain_file, domain, domainbinding);
    }

  if (
# ifdef _LIBC
      domain->conv != (__gconv_t) -1
# else
#  if HAVE_ICONV
      domain->conv != (iconv_t) -1
#  endif
# endif
      )
    {
      /* We are supposed to do a conversion.  First allocate an
	 appropriate table with the same structure as the table
	 of translations in the file, where we can put the pointers
	 to the converted strings in.
	 There is a slight complication with plural entries.  They
	 are represented by consecutive NUL terminated strings.  We
	 handle this case by converting RESULTLEN bytes, including
	 NULs.  */

      if (domain->conv_tab == NULL
	  && ((domain->conv_tab = (char **) calloc (domain->nstrings,
						    sizeof (char *)))
	      == NULL))
	/* Mark that we didn't succeed allocating a table.  */
	domain->conv_tab = (char **) -1;

      if (__builtin_expect (domain->conv_tab == (char **) -1, 0))
	/* Nothing we can do, no more memory.  */
	goto converted;

      if (domain->conv_tab[act] == NULL)
	{
	  /* We haven't used this string so far, so it is not
	     translated yet.  Do this now.  */
	  /* We use a bit more efficient memory handling.
	     We allocate always larger blocks which get used over
	     time.  This is faster than many small allocations.   */
	  __libc_lock_define_initialized (static, lock)
# define INITIAL_BLOCK_SIZE	4080
	  static unsigned char *freemem;
	  static size_t freemem_size;

	  const unsigned char *inbuf;
	  unsigned char *outbuf;
	  int malloc_count;
# ifndef _LIBC
	  transmem_block_t *transmem_list = NULL;
# endif

	  __libc_lock_lock (lock);

	  inbuf = (const unsigned char *) result;
	  outbuf = freemem + sizeof (size_t);

	  malloc_count = 0;
	  while (1)
	    {
	      transmem_block_t *newmem;
# ifdef _LIBC
	      size_t non_reversible;
	      int res;

	      if (freemem_size < sizeof (size_t))
		goto resize_freemem;

	      res = __gconv (domain->conv,
			     &inbuf, inbuf + resultlen,
			     &outbuf,
			     outbuf + freemem_size - sizeof (size_t),
			     &non_reversible);

	      if (res == __GCONV_OK || res == __GCONV_EMPTY_INPUT)
		break;

	      if (res != __GCONV_FULL_OUTPUT)
		{
		  __libc_lock_unlock (lock);
		  goto converted;
		}

	      inbuf = result;
# else
#  if HAVE_ICONV
	      const char *inptr = (const char *) inbuf;
	      size_t inleft = resultlen;
	      char *outptr = (char *) outbuf;
	      size_t outleft;

	      if (freemem_size < sizeof (size_t))
		goto resize_freemem;

	      outleft = freemem_size - sizeof (size_t);
	      if (iconv (domain->conv,
			 (ICONV_CONST char **) &inptr, &inleft,
			 &outptr, &outleft)
		  != (size_t) (-1))
		{
		  outbuf = (unsigned char *) outptr;
		  break;
		}
	      if (errno != E2BIG)
		{
		  __libc_lock_unlock (lock);
		  goto converted;
		}
#  endif
# endif

	    resize_freemem:
	      /* We must allocate a new buffer or resize the old one.  */
	      if (malloc_count > 0)
		{
		  ++malloc_count;
		  freemem_size = malloc_count * INITIAL_BLOCK_SIZE;
		  newmem = (transmem_block_t *) realloc (transmem_list,
							 freemem_size);
# ifdef _LIBC
		  if (newmem != NULL)
		    transmem_list = transmem_list->next;
		  else
		    {
		      struct transmem_list *old = transmem_list;

		      transmem_list = transmem_list->next;
		      free (old);
		    }
# endif
		}
	      else
		{
		  malloc_count = 1;
		  freemem_size = INITIAL_BLOCK_SIZE;
		  newmem = (transmem_block_t *) malloc (freemem_size);
		}
	      if (__builtin_expect (newmem == NULL, 0))
		{
		  freemem = NULL;
		  freemem_size = 0;
		  __libc_lock_unlock (lock);
		  goto converted;
		}

# ifdef _LIBC
	      /* Add the block to the list of blocks we have to free
                 at some point.  */
	      newmem->next = transmem_list;
	      transmem_list = newmem;

	      freemem = newmem->data;
	      freemem_size -= offsetof (struct transmem_list, data);
# else
	      transmem_list = newmem;
	      freemem = newmem;
# endif

	      outbuf = freemem + sizeof (size_t);
	    }

	  /* We have now in our buffer a converted string.  Put this
	     into the table of conversions.  */
	  *(size_t *) freemem = outbuf - freemem - sizeof (size_t);
	  domain->conv_tab[act] = (char *) freemem;
	  /* Shrink freemem, but keep it aligned.  */
	  freemem_size -= outbuf - freemem;
	  freemem = outbuf;
	  freemem += freemem_size & (alignof (size_t) - 1);
	  freemem_size = freemem_size & ~ (alignof (size_t) - 1);

	  __libc_lock_unlock (lock);
	}

      /* Now domain->conv_tab[act] contains the translation of all
	 the plural variants.  */
      result = domain->conv_tab[act] + sizeof (size_t);
      resultlen = *(size_t *) domain->conv_tab[act];
    }

 converted:
  /* The result string is converted.  */

#endif /* _LIBC || HAVE_ICONV */

  *lengthp = resultlen;
  return result;
}