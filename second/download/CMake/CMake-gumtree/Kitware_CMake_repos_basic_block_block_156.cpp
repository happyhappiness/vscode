{
      form->status &= ~_WINDOW_MODIFIED;
      form->status |=  _FCHECK_REQUIRED;
      Window_To_Buffer(form->w,form->current);
      wmove(form->w,form->currow,form->curcol);
    }