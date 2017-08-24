(ccase)
	{
	  while(*s++ == *buf)
	    {
	      if (*buf++=='\0') return EXACT;
	    } 
	} 
      else 
	{
	  while(toupper(*s++)==toupper(*buf))
	    {
	      if (*buf++=='\0') return EXACT;
	    }
	}