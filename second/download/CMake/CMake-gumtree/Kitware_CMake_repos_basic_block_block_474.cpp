(*bp==(
#if HAVE_LOCALE_H
		(L && L->decimal_point) ? *(L->decimal_point) :
#endif
		'.'))
	{
	  bp++;
	  while(*bp)
	    {
	      if (!isdigit(*bp)) break;
	      bp++;
	    }
	}