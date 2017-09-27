if (re == NULL)
  {
  printf("PCRE compilation failed at offset %d: %s\n", erroffset, error);
  return 1;
  }


/*************************************************************************
* If the compilation succeeded, we call PCRE again, in order to do a     *
* pattern match against the subject string. This does just ONE match. If *
* further matching is needed, it will be done below.                     *
*************************************************************************/

rc = pcre_exec(
  re,                   /* the compiled pattern */
  NULL,                 /* no extra data - we didn't study the pattern */
  subject,              /* the subject string */
  subject_length,       /* the length of the subject */
  0,                    /* start at offset 0 in the subject */
  0,                    /* default options */
  ovector,              /* output vector for substring information */
  OVECCOUNT);           /* number of elements in the output vector */

/* Matching failed: handle error cases */
