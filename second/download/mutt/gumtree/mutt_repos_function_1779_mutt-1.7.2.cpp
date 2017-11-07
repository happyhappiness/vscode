void mutt_exit (int code)
{
  mutt_endwin (NULL);
  exit (code);
}