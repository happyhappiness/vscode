(field->opts & O_PUBLIC)
            {
              if (field->drows > field->rows)
                {
                  if (form->toprow==0)
                    field->status &= ~_NEWTOP;
                  else 
                    field->status |= _NEWTOP;
                } 
              else 
                {
                  if (Justification_Allowed(field))
                    {
                      Window_To_Buffer(form->w,field);
                      werase(form->w);
                      Perform_Justification(field,form->w);
                      wsyncup(form->w);
                    }
                }
            }