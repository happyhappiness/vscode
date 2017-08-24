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