{ /* means we have to copy whole range */
                      first_modified_row = form->toprow;
                      first_unmodified_row = first_modified_row + field->rows;
                      field->status &= ~_NEWTOP;
                    }