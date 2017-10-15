  {
    strfcpy (command, entry->command, sizeof (command));

    /* rfc1524_expand_command returns 0 if the file is required */
    piped = rfc1524_expand_command (a, tempfile, type, command, sizeof (command));

    if (s->flags & MUTT_DISPLAY)
    {
      state_mark_attach (s);
      state_printf (s, _("[-- Autoview using %s --]\n"), command);
      mutt_message(_("Invoking autoview command: %s"),command);
    }

