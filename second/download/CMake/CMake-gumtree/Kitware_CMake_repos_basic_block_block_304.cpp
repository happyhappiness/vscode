{
      /* copy remaining line to window */
      waddnstr(form->w,s,(int)(s - After_End_Of_Data(s,(int)(ep - s))));
    }