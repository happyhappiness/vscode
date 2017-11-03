static void maildir_flags (char *dest, size_t destlen, HEADER * hdr)
{
  *dest = '\0';

  /*
   * The maildir specification requires that all files in the cur
   * subdirectory have the :unique string appeneded, regardless of whether
   * or not there are any flags.  If .old is set, we know that this message
   * will end up in the cur directory, so we include it in the following
   * test even though there is no associated flag.
   */
  
  if (hdr && (hdr->flagged || hdr->replied || hdr->read || hdr->deleted || hdr->old || hdr->maildir_flags))
  {
    char tmp[LONG_STRING];
    snprintf (tmp, sizeof (tmp),
	      "%s%s%s%s%s",
	      hdr->flagged ? "F" : "",
	      hdr->replied ? "R" : "",
	      hdr->read ? "S" : "", hdr->deleted ? "T" : "",
	      NONULL(hdr->maildir_flags));
    if (hdr->maildir_flags)
      qsort (tmp, strlen (tmp), 1, ch_compar);
    snprintf (dest, destlen, ":2,%s", tmp);
  }
}