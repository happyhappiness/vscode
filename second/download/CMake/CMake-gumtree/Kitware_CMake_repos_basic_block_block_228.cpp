{
  Field_Options oldopts;
  Field_Options changed_opts;
  FORM *form;
  int res = E_OK;

  if (!field)
    return(E_BAD_ARGUMENT);

  oldopts      = field->opts;
  changed_opts = oldopts ^ newopts;
  field->opts  = newopts;
  form         = field->form;

  if (form)
    {
      if (form->current == field)
        {
          field->opts = oldopts;
          return(E_CURRENT);
        }

      if (form->status & _POSTED)
        {
          if (form->curpage == field->page)
            {
              if (changed_opts & O_VISIBLE)
                {
                  if (newopts & O_VISIBLE)
                    res = Display_Field(field);
                  else
                    res = Erase_Field(field);
                }
              else
                {
                  if ((changed_opts & O_PUBLIC) &&
                      (newopts & O_VISIBLE))
                    res = Display_Field(field);
                }
            }
        }
    }

  if (changed_opts & O_STATIC)
    {
      bool single_line_field = Single_Line_Field(field);
      int res2 = E_OK;

      if (newopts & O_STATIC)
        { /* the field becomes now static */
          field->status &= ~_MAY_GROW;
          /* if actually we have no hidden columns, justification may
             occur again */
          if (single_line_field                 &&
              (field->cols == field->dcols)     &&
              (field->just != NO_JUSTIFICATION) &&
              Field_Really_Appears(field))
            {
              res2 = Display_Field(field);
            }
        }
      else
        { /* field is no longer static */
          if ((field->maxgrow==0) ||
              ( single_line_field && (field->dcols < field->maxgrow)) ||
              (!single_line_field && (field->drows < field->maxgrow)))
            {
              field->status |= _MAY_GROW;
              /* a field with justification now changes its behaviour,
                 so we must redisplay it */
              if (single_line_field                 &&
                  (field->just != NO_JUSTIFICATION) &&
                  Field_Really_Appears(field))
                {
                  res2 = Display_Field(field);
                }        
            }     
        }
      if (res2 != E_OK)
        res = res2;
    }

  return(res);
}