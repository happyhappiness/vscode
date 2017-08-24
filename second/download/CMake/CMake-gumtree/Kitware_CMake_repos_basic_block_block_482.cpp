(--(*(ap->refCount)) == 0)
	{
#if HAVE_REGEX_H_FUNCS
	  if (ap->pRegExp)
	    {
	      free(ap->refCount);
	      regfree(ap->pRegExp);
	    }
#elif HAVE_REGEXP_H_FUNCS | HAVE_REGEXPR_H_FUNCS
	  if (ap->compiled_expression)
	    {
	      free(ap->refCount);
	      free(ap->compiled_expression);
	    }
#endif
	  free(ap);
	}