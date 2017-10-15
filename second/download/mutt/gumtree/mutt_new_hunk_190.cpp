	if ((WithCrypto & APPLICATION_PGP)
            && (msg->security & APPLICATION_PGP))
	{
          if (msg->security & (ENCRYPT | SIGN))
          {
            if (mutt_yesorno (_("PGP already selected. Clear & continue ? "),
                                MUTT_YES) != MUTT_YES)
            {
              mutt_clear_error ();
              break;
            }
            msg->security &= ~(ENCRYPT | SIGN);
          }
