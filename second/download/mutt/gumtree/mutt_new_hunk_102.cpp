void mutt_forward_intro (FILE *fp, HEADER *cur)
{
  char buffer[STRING];
  
  fputs ("----- Forwarded message from ", fp);
  buffer[0] = 0;
  rfc822_write_address (buffer, sizeof (buffer), cur->env->from, 1);
  fputs (buffer, fp);
  fputs (" -----\n\n", fp);
}

void mutt_forward_trailer (FILE *fp)
{
