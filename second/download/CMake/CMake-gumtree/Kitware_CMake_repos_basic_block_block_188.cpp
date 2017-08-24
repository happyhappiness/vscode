(Is_Scroll_Field(field))
        {
          /* Again, in this case the fieldwin isn't derived from formwin,
             so we have to perform a copy operation. */
          if (Single_Line_Field(field))
            { /* horizontal scrolling */
              if (form->curcol < form->begincol)
                  form->begincol = form->curcol;
              else
                {
                  if (form->curcol >= (form->begincol + field->cols))
                      form->begincol = form->curcol - field->cols + 1;
                }
              copywin(form->w,
                      formwin,
                      0,
                      form->begincol,
                      field->frow,
                      field->fcol,
                      field->frow,
                      field->cols + field->fcol - 1,
                      0);
            }
          else
            { /* A multiline, i.e. vertical scrolling field */
              int row_after_bottom,first_modified_row,first_unmodified_row;

              if (field->drows > field->rows)
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
              if (first_unmodified_row != first_modified_row)
                copywin(form->w,
                        formwin,
                        first_modified_row,
                        0,
                        field->frow + first_modified_row - form->toprow,
                        field->fcol,
                        field->frow + first_unmodified_row - form->toprow - 1,
                        field->cols + field->fcol - 1,
                        0);
            }
          wsyncup(formwin);
        }
      else
        { /* if the field-window is simply a derived window, i.e. contains
             no invisible parts, the whole thing is trivial 
          */
          wsyncup(form->w);
        }