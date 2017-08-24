(form->status & _IN_DRIVER) 
	err = E_BAD_STATE;
      else
	{
	  if (form->curpage != page)
	    {
	      if (!_nc_Internal_Validation(form)) 
		err = E_INVALID_FIELD;
	      else
		{
		  Call_Hook(form,fieldterm);
		  Call_Hook(form,formterm);
		  err = _nc_Set_Form_Page(form,page,(FIELD *)0);
		  Call_Hook(form,forminit);
		  Call_Hook(form,fieldinit);
		  _nc_Refresh_Current_Field(form);
		}
	    }
	}