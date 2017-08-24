(There_Is_Room ||
          ((Single_Line_Field(field) && Growable(field))))
        {
          if (!There_Is_Room && !Field_Grown(field,1))
            result =  E_SYSTEM_ERROR;
          else
            {
              winsch(form->w,(chtype)C_BLANK);
              result = Wrapping_Not_Necessary_Or_Wrapping_Ok(form);
            }
        }