(fields[j]->status & _NEWPAGE)
	    {
	      pg->pmax = j-1;
	      pg++;
	      pg->pmin = j;
	    }