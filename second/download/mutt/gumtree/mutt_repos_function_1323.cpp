static void menu_redraw_prompt (MUTTMENU *menu)
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

    mutt_window_mvaddstr (menu->messagewin, 0, 0, menu->prompt);
    mutt_window_clrtoeol (menu->messagewin);
  }
}