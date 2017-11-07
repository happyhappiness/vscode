void mutt_flushinp (void)
{
  UngetCount = 0;
  MacroBufferCount = 0;
  flushinp ();
}