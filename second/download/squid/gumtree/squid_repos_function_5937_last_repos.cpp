void
manage_request()
{
    ntlmhdr *fast_header;
    char buf[NTLM_BLOB_BUFFER_SIZE];
    char decoded[NTLM_BLOB_BUFFER_SIZE];
    char *ch2, *cred = NULL;

    if (fgets(buf, NTLM_BLOB_BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "fgets() failed! dying..... errno=%d (%s)\n", errno,
                strerror(errno));
        exit(1);        /* BIIG buffer */
    }
    debug("managing request\n");
    ch2 = (char*)memchr(buf, '\n', NTLM_BLOB_BUFFER_SIZE);  /* safer against overrun than strchr */
    if (ch2) {
        *ch2 = '\0';        /* terminate the string at newline. */
    }
    debug("ntlm authenticator. Got '%s' from Squid\n", buf);

    if (memcmp(buf, "KK ", 3) == 0) {   /* authenticate-request */
        /* figure out what we got */
        struct base64_decode_ctx ctx;
        base64_decode_init(&ctx);
        size_t dstLen = 0;
        int decodedLen = 0;
        if (!base64_decode_update(&ctx, &dstLen, reinterpret_cast<uint8_t*>(decoded), strlen(buf)-3, reinterpret_cast<const uint8_t*>(buf+3)) ||
                !base64_decode_final(&ctx)) {
            SEND("NA Packet format error, couldn't base64-decode");
            return;
        }
        decodedLen = dstLen;

        if ((size_t)decodedLen < sizeof(ntlmhdr)) { /* decoding failure, return error */
            SEND("NA Packet format error, truncated packet header.");
            return;
        }
        /* fast-track-decode request type. */
        fast_header = (ntlmhdr *) decoded;

        /* sanity-check: it IS a NTLMSSP packet, isn't it? */
        if (ntlm_validate_packet(fast_header, NTLM_ANY) < 0) {
            SEND("NA Broken authentication packet");
            return;
        }
        switch (le32toh(fast_header->type)) {
        case NTLM_NEGOTIATE:
            SEND("NA Invalid negotiation request received");
            return;
        /* notreached */
        case NTLM_CHALLENGE:
            SEND("NA Got a challenge. We refuse to have our authority disputed");
            return;
        /* notreached */
        case NTLM_AUTHENTICATE:
            /* check against the DC */
            signal(SIGALRM, timeout_during_auth);
            alarm(30);
            cred = ntlm_check_auth((ntlm_authenticate *) decoded, decodedLen);
            alarm(0);
            signal(SIGALRM, SIG_DFL);
            if (got_timeout != 0) {
                fprintf(stderr, "ntlm-auth[%ld]: Timeout during authentication.\n", (long)getpid());
                SEND("BH Timeout during authentication");
                got_timeout = 0;
                return;
            }
            if (cred == NULL) {
                int smblib_err, smb_errorclass, smb_errorcode, nb_error;
                if (ntlm_errno == NTLM_ERR_LOGON) { /* hackish */
                    SEND("NA Logon Failure");
                    return;
                }
                /* there was an error. We have two errno's to look at.
                 * libntlmssp's erno is insufficient, we'll have to look at
                 * the actual SMB library error codes, to acually figure
                 * out what's happening. The thing has braindamaged interfacess..*/
                smblib_err = SMB_Get_Last_Error();
                smb_errorclass = SMBlib_Error_Class(SMB_Get_Last_SMB_Err());
                smb_errorcode = SMBlib_Error_Code(SMB_Get_Last_SMB_Err());
                nb_error = RFCNB_Get_Last_Error();
                debug("No creds. SMBlib error %d, SMB error class %d, SMB error code %d, NB error %d\n",
                      smblib_err, smb_errorclass, smb_errorcode, nb_error);
                /* Should I use smblib_err? Actually it seems I can do as well
                 * without it.. */
                if (nb_error != 0) {    /* netbios-level error */
                    SEND("BH NetBios error!");
                    fprintf(stderr, "NetBios error code %d (%s)\n", nb_error,
                            RFCNB_Error_Strings[abs(nb_error)]);
                    return;
                }
                switch (smb_errorclass) {
                case SMBC_SUCCESS:
                    debug("Huh? Got a SMB success code but could check auth..");
                    SEND("NA Authentication failed");
                    return;
                case SMBC_ERRDOS:
                    /*this is the most important one for errors */
                    debug("DOS error\n");
                    switch (smb_errorcode) {
                    /* two categories matter to us: those which could be
                     * server errors, and those which are auth errors */
                    case SMBD_noaccess: /* 5 */
                        SEND("NA Access denied");
                        return;
                    case SMBD_badformat:
                        SEND("NA bad format in authentication packet");
                        return;
                    case SMBD_badaccess:
                        SEND("NA Bad access request");
                        return;
                    case SMBD_baddata:
                        SEND("NA Bad Data");
                        return;
                    default:
                        SEND("BH DOS Error");
                        return;
                    }
                case SMBC_ERRSRV:   /* server errors */
                    debug("Server error");
                    switch (smb_errorcode) {
                    /* mostly same as above */
                    case SMBV_badpw:
                        SEND("NA Bad password");
                        return;
                    case SMBV_access:
                        SEND("NA Server access error");
                        return;
                    default:
                        SEND("BH Server Error");
                        return;
                    }
                case SMBC_ERRHRD:   /* hardware errors don't really matter */
                    SEND("BH Domain Controller Hardware error");
                    return;
                case SMBC_ERRCMD:
                    SEND("BH Domain Controller Command Error");
                    return;
                }
                SEND("BH unknown internal error.");
                return;
            }

            lc(cred);       /* let's lowercase them for our convenience */
            SEND2("AF %s", cred);
            return;
        default:
            SEND("BH unknown authentication packet type");
            return;
        }
        /* notreached */
        return;
    }
    if (memcmp(buf, "YR", 2) == 0) {    /* refresh-request */
        dc_disconnect();
        const char *ch = obtain_challenge();
        /* Robert says we can afford to wait forever. I'll trust him on this
         * one */
        while (ch == NULL) {
            sleep(30);
            ch = obtain_challenge();
        }
        SEND2("TT %s", ch);
        return;
    }
    SEND("BH Helper detected protocol error");
    return;
    /********* END ********/

}