{
    str = txtbuf;
    snprintf(txtbuf, sizeof(txtbuf), "%s (0x%08X)", txt, err);
    txtbuf[sizeof(txtbuf)-1] = '\0';

#ifdef _WIN32_WCE
    {
      wchar_t wbuf[256];
      wbuf[0] = L'\0';

      if(FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
                       FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, err, LANG_NEUTRAL,
                       wbuf, sizeof(wbuf)/sizeof(wchar_t), NULL)) {
        wcstombs(msgbuf, wbuf, sizeof(msgbuf)-1);
        msg_formatted = TRUE;
      }
    }
#else
    if(FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM |
                      FORMAT_MESSAGE_IGNORE_INSERTS,
                      NULL, err, LANG_NEUTRAL,
                      msgbuf, sizeof(msgbuf)-1, NULL)) {
      msg_formatted = TRUE;
    }
#endif
    if(msg_formatted) {
      msgbuf[sizeof(msgbuf)-1] = '\0';
      /* strip trailing '\r\n' or '\n' */
      p = strrchr(msgbuf, '\n');
      if(p && (p - msgbuf) >= 2)
        *p = '\0';
      p = strrchr(msgbuf, '\r');
      if(p && (p - msgbuf) >= 1)
        *p = '\0';
      msg = msgbuf;
    }
    if(msg)
      snprintf(outbuf, outmax, "%s - %s", str, msg);
    else
      strncpy(outbuf, str, outmax);
  }