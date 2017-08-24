(((preg->pRegExp = (regex_t*)malloc(sizeof(regex_t))) != (regex_t*)0)
       && !regcomp(preg->pRegExp,rx,
		   (REG_EXTENDED | REG_NOSUB | REG_NEWLINE) ))
	{
	  preg->refCount = (unsigned long *)malloc(sizeof(unsigned long));
	  *(preg->refCount) = 1;
	}
      else
	{
	  if (preg->pRegExp)
	    free(preg->pRegExp);
	  free(preg);
	  preg = (RegExp_Arg*)0;
	}