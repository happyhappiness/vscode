{         
              WINDOW *new_window = newpad(field->drows,field->dcols);
              if (!new_window)
                { /* restore old state */
                  field->dcols = old_dcols;
                  field->drows = old_drows;
                  field->buf   = oldbuf;
                  if (( single_line_field              && 
                        (field->dcols!=field->maxgrow)) ||
                      (!single_line_field              && 
                       (field->drows!=field->maxgrow)))
                    field->status |= _MAY_GROW;
                  free( newbuf );
                  return FALSE;
                }
              assert(form!=(FORM *)0);
              delwin(form->w);
              form->w = new_window;
              Set_Field_Window_Attributes(field,form->w);
              werase(form->w);
              Buffer_To_Window(field,form->w);
              untouchwin(form->w);
              wmove(form->w,form->currow,form->curcol);
            }