static int delete_attachment (ATTACH_CONTEXT *actx, int x)
{
  ATTACHPTR **idx = actx->idx;
  int rindex = actx->v2r[x];
  int y;

  if (rindex == 0 && actx->idxlen == 1)
  {
    mutt_error _("You may not delete the only attachment.");
    idx[rindex]->content->tagged = 0;
    return (-1);
  }

  for (y = 0; y < actx->idxlen; y++)
  {
    if (idx[y]->content->next == idx[rindex]->content)
    {
      idx[y]->content->next = idx[rindex]->content->next;
      break;
    }
  }

  idx[rindex]->content->next = NULL;
  idx[rindex]->content->parts = NULL;
  mutt_free_body (&(idx[rindex]->content));
  FREE (&idx[rindex]->tree);
  FREE (&idx[rindex]);
  for (; rindex < actx->idxlen - 1; rindex++)
    idx[rindex] = idx[rindex+1];
  idx[actx->idxlen - 1] = NULL;
  actx->idxlen--;

  return (0);
}