static void recvattach_extract_pgp_keys (ATTACH_CONTEXT *actx, MUTTMENU *menu)
{
  int i;

  if (!menu->tagprefix)
    crypt_pgp_extract_keys_from_attachment_list (CURATTACH->fp, 0, CURATTACH->content);
  else
  {
    for (i = 0; i < actx->idxlen; i++)
      if (actx->idx[i]->content->tagged)
        crypt_pgp_extract_keys_from_attachment_list (actx->idx[i]->fp, 0,
                                                     actx->idx[i]->content);
  }
}