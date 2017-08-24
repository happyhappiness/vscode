(form->currow < form->toprow)
                    {
                      form->toprow = form->currow;
                      field->status |= _NEWTOP;
                    }