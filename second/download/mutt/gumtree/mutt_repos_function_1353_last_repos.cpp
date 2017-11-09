static void
pipe_attachment_list (char *command, ATTACH_CONTEXT *actx, FILE *fp, int tag,
                      BODY *top, int filter, STATE *state)
{
  int i;

  for (i = 0; !tag || i < actx->idxlen; i++)
  {
    if (tag)
    {
      fp = actx->idx[i]->fp;
      top = actx->idx[i]->content;
    }
    if (!tag || top->tagged)
    {
      if (!filter && !option (OPTATTACHSPLIT))
	pipe_attachment (fp, top, state);
      else
	mutt_query_pipe_attachment (command, fp, top, filter);
    }
    if (!tag)
      break;
  }
}