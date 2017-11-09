static int recvattach_pgp_check_traditional (ATTACH_CONTEXT *actx, MUTTMENU *menu)
{
  int i, rv = 0;

  if (!menu->tagprefix)
    rv = crypt_pgp_check_traditional (CURATTACH->fp, CURATTACH->content, 1);
  else
  {
    for (i = 0; i < actx->idxlen; i++)
      if (actx->idx[i]->content->tagged)
        rv = rv || crypt_pgp_check_traditional (actx->idx[i]->fp, actx->idx[i]->content, 1);
  }

  return rv;
}