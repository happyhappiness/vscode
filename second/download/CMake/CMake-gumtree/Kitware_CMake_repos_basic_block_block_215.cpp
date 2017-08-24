{
  FORM *form;
  int res = E_OK;
  WINDOW *formwin;

  if (!field)
    return(E_BAD_ARGUMENT);

  if (((form=field->form) != (FORM *)0)
      && Field_Really_Appears(field))
    {    
      if (form->current==field)
        {
          Synchronize_Buffer(form);
          Set_Field_Window_Attributes(field,form->w);
          werase(form->w);
          if (field->opts & O_PUBLIC)
            {
              if (Justification_Allowed(field))
                Undo_Justification(field,form->w);
              else 
                Buffer_To_Window(field,form->w);
            }
          else 
            {
              formwin = Get_Form_Window(form); 
              copywin(form->w,formwin,
                      0,0,
                      field->frow,field->fcol,
                      field->rows-1,field->cols-1,0);
              wsyncup(formwin);
              Buffer_To_Window(field,form->w);
              field->status |= _NEWTOP; /* fake refresh to paint all */
              _nc_Refresh_Current_Field(form);
            }
        }
      else 
        {
          res = Display_Field(field);
        }
    }
  return(res);
}