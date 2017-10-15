	  if (mutt_yesorno (_("PGP already selected. Clear & continue ? "),
			      M_YES) != M_YES)
	  {
	     mutt_clear_error ();
	     break;
	  }
	  msg->security = 0;
	}
	msg->security = crypt_smime_send_menu(msg, &menu->redraw);
	redraw_crypt_lines (msg);
        mutt_message_hook (NULL, msg, M_SEND2HOOK);
        break;

