{
  FIELD  *field = form->current;
  char   *bp = Address_Of_Current_Row_In_Buffer(form);
  char   *ep = bp + field->dcols;
  char   *cp = bp + form->curcol;
  char *s;
  
  Synchronize_Buffer(form);
  if (is_blank(*cp)) 
    return E_REQUEST_DENIED; /* not in word */

  /* move cursor to begin of word and erase to end of screen-line */
  Adjust_Cursor_Position(form,
                         After_Last_Whitespace_Character(bp,form->curcol)); 
  wmove(form->w,form->currow,form->curcol);
  wclrtoeol(form->w);

  /* skip over word in buffer */
  s = Get_First_Whitespace_Character(cp,(int)(ep-cp)); 
  /* to begin of next word    */
  s = Get_Start_Of_Data(s,(int)(ep - s));
  if ( (s!=cp) && !is_blank(*s))
    {
      /* copy remaining line to window */
      waddnstr(form->w,s,(int)(s - After_End_Of_Data(s,(int)(ep - s))));
    }
  return E_OK;
}