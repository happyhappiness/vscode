void mutt_endwin (const char *msg)
{
  if (!option (OPTNOCURSES))
  {
    CLEARLINE (LINES - 1);
    
    attrset (A_NORMAL);
    mutt_refresh ();
    endwin ();
  }
  
  if (msg && *msg)
    puts (msg);
}