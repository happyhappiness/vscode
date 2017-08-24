{
          if (Last_Row && !Field_Grown(field,1))
            { /* N.B.: due to the logic in the 'if', LastRow==TRUE
                 means here that the field is growable and not
                 a single-line field */
              return(E_SYSTEM_ERROR);
            }
          wclrtoeol(form->w);
          form->currow++;
          form->curcol = 0;
          form->status |= _WINDOW_MODIFIED;
          return(E_OK);
        }