{
  FORM *form;
  int res = E_OK;

  if (!field)
    return(E_BAD_ARGUMENT);

  if (((form=field->form) != (FORM *)0)
      && Field_Really_Appears(field))
    {
      if (field == form->current)
        { 
          form->currow  = form->curcol = form->toprow = form->begincol = 0;
          werase(form->w);
      
          if ( (field->opts & O_PUBLIC) && Justification_Allowed(field) )
            Undo_Justification( field, form->w );
          else
            Buffer_To_Window( field, form->w );
          
          field->status |= _NEWTOP;
          res = _nc_Refresh_Current_Field( form );
        }
      else
        res = Display_Field( field );
    }
  field->status |= _CHANGED;
  return(res);
}