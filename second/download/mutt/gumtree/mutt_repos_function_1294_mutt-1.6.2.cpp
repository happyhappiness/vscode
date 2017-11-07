static void menu_make_entry (char *s, int l, MUTTMENU *menu, int i) 
{
  if (menu->dialog) 
  {
    strncpy (s, menu->dialog[i], l);
    menu->current = -1; /* hide menubar */
  }
  else
    menu->make_entry (s, l, menu, i);
}