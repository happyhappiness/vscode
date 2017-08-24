{
  FIELD  *field;
  WINDOW *new_window;

  if (!form || !newfield || !form->current || (newfield->form!=form))
    return(E_BAD_ARGUMENT);

  if ( (form->status & _IN_DRIVER) )
    return(E_BAD_STATE);

  if (!(form->field))
    return(E_NOT_CONNECTED);

  field = form->current;
 
  if ((field!=newfield) || 
      !(form->status & _POSTED))
    {
      if ((form->w) && 
          (field->opts & O_VISIBLE) &&
          (field->form->curpage == field->page))
        {
          _nc_Refresh_Current_Field(form);
          if (field->opts & O_PUBLIC)
            {
              if (field->drows > field->rows)
                {
                  if (form->toprow==0)
                    field->status &= ~_NEWTOP;
                  else 
                    field->status |= _NEWTOP;
                } 
              else 
                {
                  if (Justification_Allowed(field))
                    {
                      Window_To_Buffer(form->w,field);
                      werase(form->w);
                      Perform_Justification(field,form->w);
                      wsyncup(form->w);
                    }
                }
            }
          delwin(form->w);
        }
      
      field = newfield;

      if (Has_Invisible_Parts(field))
        new_window = newpad(field->drows,field->dcols);
      else 
        new_window = derwin(Get_Form_Window(form),
                            field->rows,field->cols,field->frow,field->fcol);

      if (!new_window) 
        return(E_SYSTEM_ERROR);

      form->current = field;
      form->w       = new_window;
      form->status &= ~_WINDOW_MODIFIED;
      Set_Field_Window_Attributes(field,form->w);

      if (Has_Invisible_Parts(field))
        {
          werase(form->w);
          Buffer_To_Window(field,form->w);
        } 
      else 
        {
          if (Justification_Allowed(field))
            {
              werase(form->w);
              Undo_Justification(field,form->w);
              wsyncup(form->w);
            }
        }

      untouchwin(form->w);
    }

  form->currow = form->curcol = form->toprow = form->begincol = 0;
  return(E_OK);
}