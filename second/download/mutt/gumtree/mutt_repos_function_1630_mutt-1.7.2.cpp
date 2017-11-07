static int mx_toggle_write (CONTEXT *ctx)
{
  if (!ctx)
    return -1;

  if (ctx->readonly)
  {
    mutt_error _("Cannot toggle write on a readonly mailbox!");
    return -1;
  }

  if (ctx->dontwrite)
  {
    ctx->dontwrite = 0;
    mutt_message _("Changes to folder will be written on folder exit.");
  }
  else
  {
    ctx->dontwrite = 1;
    mutt_message _("Changes to folder will not be written.");
  }

  return 0;
}