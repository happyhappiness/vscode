(!(form->status & _POSTED))
        res = E_NOT_POSTED;
      else
	res = _nc_Position_Form_Cursor(form)