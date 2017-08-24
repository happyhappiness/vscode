(form->maxpage>0)
	{
	  form->curpage = 0;
	  form_driver(form,FIRST_ACTIVE_MAGIC);
	}
      else
	{
	  form->curpage = -1;
	  form->current = (FIELD *)0;
	}