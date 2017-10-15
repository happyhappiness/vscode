void mutt_forward_trailer (FILE *fp)
{
  fputs ("\n----- End forwarded message -----\n", fp);
}