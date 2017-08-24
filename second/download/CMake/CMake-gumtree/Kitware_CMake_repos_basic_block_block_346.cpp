((result=Wrapping_Not_Necessary_Or_Wrapping_Ok(form))==E_OK)
        {
          bool End_Of_Field= (((field->drows-1)==form->currow) &&
                              ((field->dcols-1)==form->curcol));
          form->status |= _WINDOW_MODIFIED;
          if (End_Of_Field && !Growable(field) && (field->opts & O_AUTOSKIP))
            result = Inter_Field_Navigation(FN_Next_Field,form);
          else
            {
              if (End_Of_Field && Growable(field) && !Field_Grown(field,1))
                result = E_SYSTEM_ERROR;
              else
                {
                  IFN_Next_Character(form);
                  result = E_OK;
                }
            }
        }