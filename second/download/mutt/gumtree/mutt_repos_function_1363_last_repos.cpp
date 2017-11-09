void mutt_attach_init (ATTACH_CONTEXT *actx)
{
  int i;

  for (i = 0; i < actx->idxlen; i++)
  {
    actx->idx[i]->content->tagged = 0;
    if (option (OPTDIGESTCOLLAPSE) &&
        actx->idx[i]->content->type == TYPEMULTIPART &&
	!ascii_strcasecmp (actx->idx[i]->content->subtype, "digest"))
      actx->idx[i]->content->collapsed = 1;
    else
      actx->idx[i]->content->collapsed = 0;
  }
}