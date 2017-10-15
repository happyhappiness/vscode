      case OP_COMPOSE_PGP_MENU:
        if (!(WithCrypto & APPLICATION_PGP))
          break;
	if ((WithCrypto & APPLICATION_SMIME)
            && (msg->security & APPLICATION_SMIME))
	{
	  if (mutt_yesorno (_("S/MIME already selected. Clear & continue ? "),
			     M_YES) != M_YES)
	  {
	    mutt_clear_error ();
	    break;
	  }
	  msg->security &= ~APPLICATION_SMIME;
	  msg->security |= APPLICATION_PGP;
	}
	msg->security = crypt_pgp_send_menu (msg, &menu->redraw);
	redraw_crypt_lines (msg);
        mutt_message_hook (NULL, msg, M_SEND2HOOK);
        break;

