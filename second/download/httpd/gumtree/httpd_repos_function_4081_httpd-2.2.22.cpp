static BOOL
match_ref(int offset, register const uschar *eptr, int length, match_data *md,
  unsigned long int ims)
{
const uschar *p = md->start_subject + md->offset_vector[offset];

#ifdef DEBUG
if (eptr >= md->end_subject)
  printf("matching subject <null>");
else
  {
  printf("matching subject ");
  pchars(eptr, length, TRUE, md);
  }
printf(" against backref ");
pchars(p, length, FALSE, md);
printf("\n");
#endif

/* Always fail if not enough characters left */

if (length > md->end_subject - eptr) return FALSE;

/* Separate the caselesss case for speed */

if ((ims & PCRE_CASELESS) != 0)
  {
  while (length-- > 0)
    if (md->lcc[*p++] != md->lcc[*eptr++]) return FALSE;
  }
else
  { while (length-- > 0) if (*p++ != *eptr++) return FALSE; }

return TRUE;
}