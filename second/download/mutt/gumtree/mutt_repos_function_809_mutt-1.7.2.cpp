static int select_file_search (MUTTMENU *menu, regex_t *re, int n)
{
  return (regexec (re, ((struct folder_file *) menu->data)[n].name, 0, NULL, 0));
}