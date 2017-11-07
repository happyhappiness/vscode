void folder_entry (char *s, size_t slen, MUTTMENU *menu, int num)
{
  FOLDER folder;

  folder.ff = &((struct folder_file *) menu->data)[num];
  folder.num = num;
  
  mutt_FormatString (s, slen, NONULL(FolderFormat), folder_format_str, 
      (unsigned long) &folder, M_FORMAT_ARROWCURSOR);
}