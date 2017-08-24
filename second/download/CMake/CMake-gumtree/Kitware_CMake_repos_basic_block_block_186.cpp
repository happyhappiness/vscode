(field->drows > field->rows)
                {
                  row_after_bottom = form->toprow + field->rows;
                  if (form->currow < form->toprow)
                    {
                      form->toprow = form->currow;
                      field->status |= _NEWTOP;
                    }
                  if (form->currow >= row_after_bottom)
                    {
                      form->toprow = form->currow - field->rows + 1;
                      field->status |= _NEWTOP;
                    }
                  if (field->status & _NEWTOP)
                    { /* means we have to copy whole range */
                      first_modified_row = form->toprow;
                      first_unmodified_row = first_modified_row + field->rows;
                      field->status &= ~_NEWTOP;
                    }
                  else 
                    { /* we try to optimize : finding the range of touched
                         lines */
                      first_modified_row = form->toprow;
                      while(first_modified_row < row_after_bottom)
                        {
                          if (is_linetouched(form->w,first_modified_row)) 
                            break;
                          first_modified_row++;
                        }
                      first_unmodified_row = first_modified_row;
                      while(first_unmodified_row < row_after_bottom)
                        {
                          if (!is_linetouched(form->w,first_unmodified_row)) 
                            break;
                          first_unmodified_row++;
                        }
                    }
                }
              else
                {
                  first_modified_row   = form->toprow;
                  first_unmodified_row = first_modified_row + field->rows;
                }