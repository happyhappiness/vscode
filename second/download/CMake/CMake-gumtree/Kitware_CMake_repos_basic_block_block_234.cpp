{
                      Window_To_Buffer(form->w,field);
                      werase(form->w);
                      Perform_Justification(field,form->w);
                      wsyncup(form->w);
                    }