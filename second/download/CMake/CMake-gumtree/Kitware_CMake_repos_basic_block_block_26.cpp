(!_nc_Internal_Validation(form)) 
	       err = E_INVALID_FIELD;
	      else
		{
		  Call_Hook(form,fieldterm);
		  if (field->page != form->curpage)
		    {
		      Call_Hook(form,formterm);
		      err = _nc_Set_Form_Page(form,field->page,field);
		      Call_Hook(form,forminit);
		    } 
		  else 
		    {
		      err = _nc_Set_Current_Field(form,field);
		    }
		  Call_Hook(form,fieldinit);
		  _nc_Refresh_Current_Field(form);
		}