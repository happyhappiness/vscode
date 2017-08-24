{
  FIELD  *field;
  WINDOW *formwin;
  
  if (!form)
    return(E_BAD_ARGUMENT);

  if (!form->w || !form->current) 
    return(E_SYSTEM_ERROR);

  field    = form->current;
  formwin  = Get_Form_Window(form);

  wmove( form->w, form->currow, form->curcol );
  if ( Has_Invisible_Parts(field) )
    {
      /* in this case fieldwin isn't derived from formwin, so we have
         to move the cursor in formwin by hand... */
      wmove(formwin,
            field->frow + form->currow - form->toprow,
            field->fcol + form->curcol - form->begincol);
      wcursyncup(formwin);
    }
  else 
    wcursyncup(form->w);
  return(E_OK);
}