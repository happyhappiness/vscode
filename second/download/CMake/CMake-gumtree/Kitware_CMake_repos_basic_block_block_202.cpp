{
  WINDOW *win;
  WINDOW *fwin;

  if (!field)
    return E_SYSTEM_ERROR;

  fwin = Get_Form_Window(field->form);
  win  = derwin(fwin,
                field->rows,field->cols,field->frow,field->fcol);

  if (!win) 
    return E_SYSTEM_ERROR;
  else
    {
      if (field->opts & O_VISIBLE)
        Set_Field_Window_Attributes(field,win);
      else
        {
#if defined(__LSB_VERSION__)
        /* getattrs() would be handy, but it is not part of LSB 4.0 */
        attr_t fwinAttrs;
        short  fwinPair;
        wattr_get(fwin, &fwinAttrs, &fwinPair, 0);
        wattr_set(win, fwinAttrs, fwinPair, 0);
#else
        wattrset(win,getattrs(fwin));
#endif
        }
      werase(win);
    }

  if (!bEraseFlag)
    {
      if (field->opts & O_PUBLIC)
        {
          if (Justification_Allowed(field))
            Perform_Justification(field,win);
          else
            Buffer_To_Window(field,win);
        }
      field->status &= ~_NEWTOP;
    }
  wsyncup(win);
  delwin(win);
  return E_OK;
}