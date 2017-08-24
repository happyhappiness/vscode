{ 
          split = After_Last_Whitespace_Character(bp,
                    (int)(Get_Start_Of_Data(bp + field->dcols - requiredlen ,
                                            requiredlen) - bp));
          /* split points now to the first character of the portion of the
             line that must be moved to the next line */
          datalen = (int)(split-bp); /* + freelen has to stay on this line   */
          freelen = field->dcols - (datalen + freelen); /* for the next line */

          if ((result=Insert_String(form,row+1,split,freelen))==E_OK) 
            {
              wmove(form->w,row,datalen);
              wclrtoeol(form->w);
              wmove(form->w,row,0);
              winsnstr(form->w,txt,len);
              wmove(form->w,row,len);
              winsnstr(form->w,Space,1);
              free(Space);
              return E_OK;
            }
        }