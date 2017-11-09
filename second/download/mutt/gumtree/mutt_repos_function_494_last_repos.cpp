void mutt_curs_set (int cursor)
{
  static int SavedCursor = 1;
  
  if (cursor < 0)
    cursor = SavedCursor;
  else
    SavedCursor = cursor;
  
  if (curs_set (cursor) == ERR) {
    if (cursor == 1)	/* cnorm */
      curs_set (2);	/* cvvis */
  }
}