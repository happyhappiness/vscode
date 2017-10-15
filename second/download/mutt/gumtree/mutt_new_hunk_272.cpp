	need_pause = 1;
      }
    }
  }

  /* Read the user's initialization file.  */
  if (Muttrc)
  {
    if (!option (OPTNOCURSES))
      endwin ();
    if (source_rc (Muttrc, &err) != 0)
    {
      fputs (err.data, stderr);
      fputc ('\n', stderr);
      need_pause = 1;
    }
  }

  if (mutt_execute_commands (commands) != 0)
    need_pause = 1;

  if (need_pause && !option (OPTNOCURSES))
  {
