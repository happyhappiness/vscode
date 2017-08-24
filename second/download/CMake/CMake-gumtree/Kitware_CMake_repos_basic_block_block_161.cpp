(!new_window)
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