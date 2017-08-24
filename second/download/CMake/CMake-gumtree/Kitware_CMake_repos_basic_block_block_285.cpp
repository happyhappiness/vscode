(chars_to_remain_on_line > 0)
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