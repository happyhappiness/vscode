error_t
argz_insert (char **pargz, size_t *pargz_len, char *before, const char *entry)
{
  assert (pargz);
  assert (pargz_len);
  assert (entry && *entry);

  /* No BEFORE address indicates ENTRY should be inserted after the
     current last element.  */
  if (!before)
    return argz_append (pargz, pargz_len, entry, 1+ strlen (entry));

  /* This probably indicates a programmer error, but to preserve
     semantics, scan back to the start of an entry if BEFORE points
     into the middle of it.  */
  while ((before > *pargz) && (before[-1] != EOS_CHAR))
    --before;

  {
    size_t entry_len	= 1+ strlen (entry);
    size_t argz_len	= *pargz_len + entry_len;
    size_t offset	= before - *pargz;
    char   *argz	= (char *) realloc (*pargz, argz_len);

    if (!argz)
      return ENOMEM;

    /* Make BEFORE point to the equivalent offset in ARGZ that it
       used to have in *PARGZ incase realloc() moved the block.  */
    before = argz + offset;

    /* Move the ARGZ entries starting at BEFORE up into the new
       space at the end -- making room to copy ENTRY into the
       resulting gap.  */
    memmove (before + entry_len, before, *pargz_len - offset);
    memcpy  (before, entry, entry_len);

    /* Assign new values.  */
    *pargz = argz;
    *pargz_len = argz_len;
  }

  return 0;
}