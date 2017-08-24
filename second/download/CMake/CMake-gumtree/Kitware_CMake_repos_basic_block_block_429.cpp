{
  char **kwds       = ((const enumARG *)argp)->kwds;
  bool ccase        = ((const enumARG *)argp)->checkcase;
  bool unique       = ((const enumARG *)argp)->checkunique;
  unsigned char *bp = (unsigned char *)field_buffer(field,0);
  char *s, *t, *p;
  int res;
  
  while( kwds && (s=(*kwds++)) )
    {
      if ((res=Compare((unsigned char *)s,bp,ccase))!=NOMATCH)
	{
	  p=t=s; /* t is at least a partial match */
	  if ((unique && res!=EXACT)) 
	    {
	      while( kwds && (p = *kwds++) )
		{
		  if ((res=Compare((unsigned char *)p,bp,ccase))!=NOMATCH)
		    {
		      if (res==EXACT)
			{
			  t = p;
			  break;
			}
		      else
			t = (char *)0;
		    }
		}
	    }	  
	  if (t)
	    {
	      set_field_buffer(field,0,t);
	      return TRUE;
	    }
	  if (!p)
	    break;
	}
    }
  return FALSE;
}