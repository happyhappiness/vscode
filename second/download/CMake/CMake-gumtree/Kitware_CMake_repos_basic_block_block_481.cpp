(ap->pRegExp)
	    {
	      free(ap->refCount);
	      regfree(ap->pRegExp);
	    }