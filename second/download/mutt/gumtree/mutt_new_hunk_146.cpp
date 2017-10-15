        if (!(WithCrypto & APPLICATION_SMIME))
          break;

	if ((WithCrypto & APPLICATION_PGP)
            && (msg->security & APPLICATION_PGP))
	{
          if (msg->security & (ENCRYPT | SIGN))
	  {
            if (mutt_yesorno (_("PGP already selected. Clear & continue ? "),
                                M_YES) != M_YES)
            {
              mutt_clear_error ();
              break;
            }
            msg->security &= ~(ENCRYPT | SIGN);
	  }
	  msg->security &= ~APPLICATION_PGP;
	  msg->security |= APPLICATION_SMIME;
          crypt_opportunistic_encrypt (msg);
          redraw_crypt_lines (msg);
	}
	msg->security = crypt_smime_send_menu(msg, &menu->redraw);
	redraw_crypt_lines (msg);
        mutt_message_hook (NULL, msg, M_SEND2HOOK);
        break;

