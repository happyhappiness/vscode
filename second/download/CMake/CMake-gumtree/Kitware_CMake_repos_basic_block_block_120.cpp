r(fields=form->field;*fields;fields++)
	{
	  if (form == (*fields)->form) 
	    (*fields)->form = (FORM *)0;
	}