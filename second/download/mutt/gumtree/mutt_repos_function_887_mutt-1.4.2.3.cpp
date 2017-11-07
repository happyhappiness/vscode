void menu_redraw_prompt (MUTTMENU *menu)
{
  if (menu->dialog) 
  {
    if (option (OPTMSGERR)) 
    {
      mutt_sleep (1);
      unset_option (OPTMSGERR);
    }

    if (*Errorbuf)
      mutt_clear_error ();

    SETCOLOR (MT_COLOR_NORMAL);
    mvaddstr (LINES - 1, 0, menu->prompt);
    clrtoeol ();
  }
}