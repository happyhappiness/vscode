((err=Associate_Fields(form,fields))!=E_OK)
	{
	  free_form(form);
	  form = (FORM *)0;
	}