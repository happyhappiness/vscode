void mutt_pipe_message (HEADER *h)
{
  char buffer[LONG_STRING];

  buffer[0] = 0;
  if (mutt_get_field (_("Pipe to command: "), buffer, sizeof (buffer), MUTT_CMD)
      != 0 || !buffer[0])
    return;

  mutt_expand_path (buffer, sizeof (buffer));
  _mutt_pipe_message (h, buffer,
		      option (OPTPIPEDECODE),
		      0, 
		      option (OPTPIPESPLIT),
		      PipeSep);
}