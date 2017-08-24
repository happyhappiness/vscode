{
      char *bp;
      char *split;
      int chars_to_be_wrapped;
      int chars_to_remain_on_line;
      if (Last_Row)
        { /* the above logic already ensures, that in this case the field
             is growable */
          if (!Field_Grown(field,1))
            return E_SYSTEM_ERROR;
        }
      bp = Address_Of_Current_Row_In_Buffer(form);
      Window_To_Buffer(form->w,field);
      split = After_Last_Whitespace_Character(bp,field->dcols);
      /* split points to the first character of the sequence to be brought
         on the next line */
      chars_to_remain_on_line = (int)(split - bp);
      chars_to_be_wrapped     = field->dcols - chars_to_remain_on_line;
      if (chars_to_remain_on_line > 0)
        {
          if ((result=Insert_String(form,form->currow+1,split,
                                    chars_to_be_wrapped)) == E_OK)
            {
              wmove(form->w,form->currow,chars_to_remain_on_line);
              wclrtoeol(form->w);
              if (form->curcol >= chars_to_remain_on_line)
                {
                  form->currow++;
                  form->curcol -= chars_to_remain_on_line;
                }
              return E_OK;
            }
        }
      else
        return E_OK;
      if (result!=E_OK)
        {
          wmove(form->w,form->currow,form->curcol);
          wdelch(form->w);
          Window_To_Buffer(form->w,field);
          result = E_REQUEST_DENIED;
        }
    }