                 nb_error = RFCNB_Get_Last_Error();
                 debug("No creds. SMBlib error %d, SMB error class %d, SMB error code %d, NB error %d\n",
                       smblib_err, smb_errorclass, smb_errorcode, nb_error);
                 /* Should I use smblib_err? Actually it seems I can do as well
                  * without it.. */
                 if (nb_error != 0) {	/* netbios-level error */
-                    send_bh_or_ld("NetBios error!",
-                                  (ntlm_authenticate *) decoded, decodedLen);
+                    SEND("BH NetBios error!");
                     fprintf(stderr, "NetBios error code %d (%s)\n", nb_error,
                             RFCNB_Error_Strings[abs(nb_error)]);
                     return;
                 }
                 switch (smb_errorclass) {
                 case SMBC_SUCCESS:
                     debug("Huh? Got a SMB success code but could check auth..");
                     SEND("NA Authentication failed");
-                    /*
-                     * send_bh_or_ld("SMB success, but no creds. Internal error?",
-                     * (ntlm_authenticate *) decoded, decodedLen);
-                     */
                     return;
                 case SMBC_ERRDOS:
                     /*this is the most important one for errors */
                     debug("DOS error\n");
                     switch (smb_errorcode) {
                         /* two categories matter to us: those which could be
