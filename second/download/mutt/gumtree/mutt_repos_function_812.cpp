static int file_tag (MUTTMENU *menu, int n, int m)
{
  struct folder_file *ff = &(((struct folder_file *)menu->data)[n]);
  int ot;
  if (S_ISDIR (ff->mode) || (S_ISLNK (ff->mode) && link_is_dir (LastDir, ff->name)))
  {
    mutt_error _("Can't attach a directory!");
    return 0;
  }
  
  ot = ff->tagged;
  ff->tagged = (m >= 0 ? m : !ff->tagged);
  
  return ff->tagged - ot;
}