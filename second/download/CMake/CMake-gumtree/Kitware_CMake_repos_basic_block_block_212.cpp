{
              formwin = Get_Form_Window(form); 
              copywin(form->w,formwin,
                      0,0,
                      field->frow,field->fcol,
                      field->rows-1,field->cols-1,0);
              wsyncup(formwin);
              Buffer_To_Window(field,form->w);
              field->status |= _NEWTOP; /* fake refresh to paint all */
              _nc_Refresh_Current_Field(form);
            }