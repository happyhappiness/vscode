 	if ((WithCrypto & APPLICATION_SMIME)
             && (msg->security & APPLICATION_SMIME))
 	{
           if (msg->security & (ENCRYPT | SIGN))
           {
             if (mutt_yesorno (_("S/MIME already selected. Clear & continue ? "),
-                              M_YES) != M_YES)
+                              MUTT_YES) != MUTT_YES)
             {
               mutt_clear_error ();
               break;
             }
             msg->security &= ~(ENCRYPT | SIGN);
           }
