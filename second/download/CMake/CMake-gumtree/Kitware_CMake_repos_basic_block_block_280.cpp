{
          wmove(form->w,form->currow,form->curcol);
          wdelch(form->w);
          Window_To_Buffer(form->w,field);
          result = E_REQUEST_DENIED;
        }