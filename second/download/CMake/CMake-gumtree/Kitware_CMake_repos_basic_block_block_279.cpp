{
      wmove(form->w,row,0);
      winsnstr(form->w,txt,len);
      wmove(form->w,row,len);
      winsnstr(form->w,Space,1);
      free(Space);
      return E_OK;
    }