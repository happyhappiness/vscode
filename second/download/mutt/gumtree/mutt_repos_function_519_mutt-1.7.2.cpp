static struct mx_ops* mx_get_ops (int magic)
{
  switch (magic)
  {
#ifdef USE_IMAP
    case MUTT_IMAP:
      return &mx_imap_ops;
#endif
    case MUTT_MAILDIR:
      return &mx_maildir_ops;
    case MUTT_MBOX:
      return &mx_mbox_ops;
    case MUTT_MH:
      return &mx_mh_ops;
    case MUTT_MMDF:
      return &mx_mmdf_ops;
#ifdef USE_POP
    case MUTT_POP:
      return &mx_pop_ops;
#endif
    default:
      return NULL;
  }
}