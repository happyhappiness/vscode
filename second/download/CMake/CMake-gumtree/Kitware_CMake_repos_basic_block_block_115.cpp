(current==head)
	    { /* We cycled through. Reset head to indicate that */
	      head = (FIELD *)0;
	      break;
	    }