static void maildir_flags (char *dest, size_t destlen, HEADER *hdr)
{
  /*
   * The maildir specification requires that all files in the cur
   * subdirectory have the :unique string appeneded, regardless of whether
   * or not there are any flags.  If .old is set, we know that this message
   * will end up in the cur directory, so we include it in the following
   * test even though there is no associated flag.
   */
  if (hdr->flagged || hdr->replied || hdr->read || hdr->deleted || hdr->old)
  {
    snprintf (dest, destlen, 
	      ":2,%s%s%s%s",
	     hdr->flagged ? "F" : "",
	     hdr->replied ? "R" : "",
	     hdr->read ? "S" : "",
	     hdr->deleted ? "T" : "");
  }
  else
    *dest = '\0';
}