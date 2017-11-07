void mutt_flushinp (void)
{
  UngetCount = 0;
  flushinp ();
}