int
regexec(regex_t *preg, const char *string, size_t nmatch,
  regmatch_t pmatch[], int eflags)
{
int rc;
int options = 0;
/* NOTE: The code related to the "SMALL_NMATCH" optimization
 * currently is unique to the httpd-2.0 copy of PCRE 3.9.  I've
 * submitted the patch to the PCRE maintainer for inclusion in
 * the next PCRE release, slated for late 2002.  At that time,
 * we can merge the new PCRE version into the httpd-2.0/srclib
 * tree.  --brianp 3/20/2002
 */
int small_ovector[SMALL_NMATCH * 3];
int *ovector = NULL;
int allocated_ovector = 0;

if ((eflags & REG_NOTBOL) != 0) options |= PCRE_NOTBOL;
if ((eflags & REG_NOTEOL) != 0) options |= PCRE_NOTEOL;

#if 0
/* This causes a memory segfault after locking the const, thread-shared *preg 
 * generated at compile time, and is entirely unnecessary.
 */
preg->re_erroffset = (size_t)(-1);   /* Only has meaning after compile */
#endif

if (nmatch > 0)
  {
    if (nmatch <= SMALL_NMATCH)
      {
      ovector = &(small_ovector[0]);
      }
    else
      {
      ovector = (int *)malloc(sizeof(int) * nmatch * 3);
      if (ovector == NULL) return REG_ESPACE;
      allocated_ovector = 1;
      }
  }

rc = pcre_exec(preg->re_pcre, NULL, string, (int)strlen(string), 0, options,
  ovector, nmatch * 3);

if (rc == 0) rc = nmatch;    /* All captured slots were filled in */

if (rc >= 0)
  {
  size_t i;
  for (i = 0; i < (size_t) rc; i++)
    {
    pmatch[i].rm_so = ovector[i*2];
    pmatch[i].rm_eo = ovector[i*2+1];
    }
  if (allocated_ovector) free(ovector);
  for (; i < nmatch; i++) pmatch[i].rm_so = pmatch[i].rm_eo = -1;
  return 0;
  }

else
  {
  if (allocated_ovector) free(ovector);
  switch(rc)
    {
    case PCRE_ERROR_NOMATCH: return REG_NOMATCH;
    case PCRE_ERROR_NULL: return REG_INVARG;
    case PCRE_ERROR_BADOPTION: return REG_INVARG;
    case PCRE_ERROR_BADMAGIC: return REG_INVARG;
    case PCRE_ERROR_UNKNOWN_NODE: return REG_ASSERT;
    case PCRE_ERROR_NOMEMORY: return REG_ESPACE;
    default: return REG_ASSERT;
    }
  }
}