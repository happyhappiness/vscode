{
      char *this_line, *prev_line, *prev_end, *this_end;
      
      form->curcol++;
      if (form->status & _OVLMODE) 
        return E_REQUEST_DENIED;
      
      prev_line = Address_Of_Row_In_Buffer(field,(form->currow-1));
      this_line = Address_Of_Row_In_Buffer(field,(form->currow));
      Synchronize_Buffer(form);
      prev_end = After_End_Of_Data(prev_line,field->dcols);
      this_end = After_End_Of_Data(this_line,field->dcols);
      if ((int)(this_end-this_line) > 
          (field->cols-(int)(prev_end-prev_line))) 
        return E_REQUEST_DENIED;
      wdeleteln(form->w);
      Adjust_Cursor_Position(form,prev_end);
      wmove(form->w,form->currow,form->curcol);
      waddnstr(form->w,this_line,(int)(this_end-this_line));
    }