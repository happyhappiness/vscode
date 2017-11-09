static void recvattach_edit_content_type (ATTACH_CONTEXT *actx, MUTTMENU *menu, HEADER *hdr)
{
  int i;

  if (mutt_edit_content_type (hdr, CURATTACH->content, CURATTACH->fp) == 1)
  {
    /* The mutt_update_recvattach_menu() will overwrite any changes
     * made to a decrypted CURATTACH->content, so warn the user. */
    if (CURATTACH->decrypted)
    {
      mutt_message _("Structural changes to decrypted attachments are not supported");
      mutt_sleep (1);
    }
    /* Editing the content type can rewrite the body structure. */
    for (i = 0; i < actx->idxlen; i++)
      actx->idx[i]->content = NULL;
    mutt_actx_free_entries (actx);
    mutt_update_recvattach_menu (actx, menu, 1);
  }
}