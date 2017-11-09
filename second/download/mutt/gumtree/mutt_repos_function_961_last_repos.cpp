int rfc1524_expand_filename (char *nametemplate,
			     char *oldfile, 
			     char *newfile,
			     size_t nflen)
{
  int i, j, k, ps;
  char *s;
  short lmatch = 0, rmatch = 0; 
  char left[_POSIX_PATH_MAX];
  char right[_POSIX_PATH_MAX];
  
  newfile[0] = 0;

  /* first, ignore leading path components.
   */
  
  if (nametemplate && (s = strrchr (nametemplate, '/')))
    nametemplate = s + 1;

  if (oldfile && (s = strrchr (oldfile, '/')))
    oldfile = s + 1;
    
  if (!nametemplate)
  {
    if (oldfile)
      strfcpy (newfile, oldfile, nflen);
  }
  else if (!oldfile)
  {
    mutt_expand_fmt (newfile, nflen, nametemplate, "mutt");
  }
  else /* oldfile && nametemplate */
  {

    /* first, compare everything left from the "%s" 
     * (if there is one).
     */
    
    lmatch = 1; ps = 0;
    for(i = 0; nametemplate[i]; i++)
    {
      if(nametemplate[i] == '%' && nametemplate[i+1] == 's')
      { 
	ps = 1;
	break;
      }

      /* note that the following will _not_ read beyond oldfile's end. */

      if(lmatch && nametemplate[i] != oldfile[i])
	lmatch = 0;
    }

    if(ps)
    {
      
      /* If we had a "%s", check the rest. */
      
      /* now, for the right part: compare everything right from 
       * the "%s" to the final part of oldfile.
       * 
       * The logic here is as follows:
       * 
       * - We start reading from the end.
       * - There must be a match _right_ from the "%s",
       *   thus the i + 2.  
       * - If there was a left hand match, this stuff
       *   must not be counted again.  That's done by the
       *   condition (j >= (lmatch ? i : 0)).
       */
      
      rmatch = 1;

      for(j = mutt_strlen(oldfile) - 1, k = mutt_strlen(nametemplate) - 1 ;
	  j >= (lmatch ? i : 0) && k >= i + 2;
	  j--, k--)
      {
	if(nametemplate[k] != oldfile[j])
	{
	  rmatch = 0;
	  break;
	}
      }
      
      /* Now, check if we had a full match. */
      
      if(k >= i + 2)
	rmatch = 0;
      
      if(lmatch) *left = 0;
      else strnfcpy(left, nametemplate, sizeof(left), i);
      
      if(rmatch) *right = 0;
      else strfcpy(right, nametemplate + i + 2, sizeof(right));
      
      snprintf(newfile, nflen, "%s%s%s", left, oldfile, right);
    }
    else
    {
      /* no "%s" in the name template. */
      strfcpy(newfile, nametemplate, nflen);
    }
  }
  
  mutt_adv_mktemp(newfile, nflen);

  if(rmatch && lmatch)
    return 0;
  else 
    return 1;
  
}