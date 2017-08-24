((res=Compare((unsigned char *)p,bp,ccase))!=NOMATCH)
		    {
		      if (res==EXACT)
			{
			  t = p;
			  break;
			}
		      else
			t = (char *)0;
		    }