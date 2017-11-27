static char *
argz_next (argz, argz_len, entry)
     char *argz;
     size_t argz_len;
     const char *entry;
{
  assert ((argz && argz_len) || (!argz && !argz_len));

  if (entry)
    {
      /* Either ARGZ/ARGZ_LEN is empty, or ENTRY points into an address
	 within the ARGZ vector.  */
      assert ((!argz && !argz_len)
	      || ((argz <= entry) && (entry < (argz + argz_len))));

      /* Move to the char immediately after the terminating
	 '\0' of ENTRY.  */
      entry = 1+ strchr (entry, LT_EOS_CHAR);

      /* Return either the new ENTRY, or else NULL if ARGZ is
	 exhausted.  */
      return (entry >= argz + argz_len) ? 0 : (char *) entry;
    }
  else
    {
      /* This should probably be flagged as a programmer error,
	 since starting an argz_next loop with the iterator set
	 to ARGZ is safer.  To preserve semantics, handle the NULL
	 case by returning the start of ARGZ (if any).  */
      if (argz_len > 0)
	return argz;
      else
	return 0;
    }
}