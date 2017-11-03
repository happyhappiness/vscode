static void
pipe_attachment_list (char *command, FILE *fp, int tag, BODY *top, int filter,
		      STATE *state)
{
  for (; top; top = top->next)
  {
    if (!tag || top->tagged)
    {
      if (!filter && !option (OPTATTACHSPLIT))
	pipe_attachment (fp, top, state);
      else
	mutt_query_pipe_attachment (command, fp, top, filter);
    }
    else if (top->parts)
      pipe_attachment_list (command, fp, tag, top->parts, filter, state);
    if (!tag)
      break;
  }
}