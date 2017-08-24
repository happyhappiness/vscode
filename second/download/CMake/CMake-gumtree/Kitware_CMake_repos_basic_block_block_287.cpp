{
          bool May_Do_It = !Last_Row && Is_There_Room_For_A_Line(form);
          
          if (!(May_Do_It || Growable(field)))
            return(E_REQUEST_DENIED);
          if (!May_Do_It && !Field_Grown(field,1))
            return(E_SYSTEM_ERROR);
          
          bp= Address_Of_Current_Position_In_Buffer(form);
          t = After_End_Of_Data(bp,field->dcols - form->curcol);
          wclrtoeol(form->w);
          form->currow++;
          form->curcol=0;
          wmove(form->w,form->currow,form->curcol);
          winsertln(form->w);
          waddnstr(form->w,bp,(int)(t-bp));
          form->status |= _WINDOW_MODIFIED;
          return E_OK;
        }