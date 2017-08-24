{
  FIELD *field = form->current;
  char  *bp    = Address_Of_Current_Position_In_Buffer(form);
  char  *s;
  char  *t;
  bool  again = FALSE;

  /* We really need access to the data, so we have to synchronize */
  Synchronize_Buffer(form);

  s = After_End_Of_Data(field->buf,(int)(bp-field->buf));
  /* s points now right after the last non-blank in the buffer before bp.
     If bp was in a word, s equals bp. In this case we must find the last
     whitespace in the buffer before bp and repeat the game to really find
     the previous word! */
  if (s==bp)
    again = TRUE;
  
  /* And next call now goes backward to look for the last whitespace
     before that, pointing right after this, so it points to the begin
     of the previous word. 
  */
  t = After_Last_Whitespace_Character(field->buf,(int)(s - field->buf));
#if !FRIENDLY_PREV_NEXT_WORD
  if (s==t) 
    return(E_REQUEST_DENIED);
#endif
  if (again)
    { /* and do it again, replacing bp by t */
      s = After_End_Of_Data(field->buf,(int)(t - field->buf));
      t = After_Last_Whitespace_Character(field->buf,(int)(s - field->buf));
#if !FRIENDLY_PREV_NEXT_WORD
      if (s==t) 
        return(E_REQUEST_DENIED);
#endif
    }
  Adjust_Cursor_Position(form,t);
  return(E_OK);
}