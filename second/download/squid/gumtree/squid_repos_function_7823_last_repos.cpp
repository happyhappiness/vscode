int SMB_Logon_Server(SMB_Handle_Type Con_Handle, char *UserName,
                     char *PassWord, const char *NtDomain, int PreCrypted)

{
    struct RFCNB_Pkt *pkt;
    int param_len, pkt_len, pass_len;
    char *p, pword[128];

    /* First we need a packet etc ... but we need to know what protocol has  */
    /* been negotiated to figure out if we can do it and what SMB format to  */
    /* use ...                                                               */

    if (Con_Handle -> protocol < SMB_P_LanMan1) {

        SMBlib_errno = SMBlibE_ProtLow;
        return(SMBlibE_BAD);

    }

    if (PreCrypted) {
        pass_len = 24;
        memcpy(pword, PassWord, 24);
    } else {
        strncpy(pword, PassWord, sizeof(pword));
        pword[sizeof(pword) - 1] = '\0';
#ifdef PAM_SMB_ENC_PASS
        if (Con_Handle->encrypt_passwords) {
            pass_len = 24;
            SMBencrypt((uchar *) PassWord, (uchar *) Con_Handle->Encrypt_Key, (uchar *) pword);
        } else
#endif
            pass_len = strlen(pword);
    }

    /* Now build the correct structure */

    if (Con_Handle -> protocol < SMB_P_NT1) {

        /* We don't handle encrypted passwords ... */

        param_len = strlen(UserName) + 1 + pass_len + 1 +
                    (NtDomain!=NULL ? strlen(NtDomain) : strlen(Con_Handle->PDomain)) + 1 +
                    strlen(Con_Handle -> OSName) + 1;

        pkt_len = SMB_ssetpLM_len + param_len;

        pkt = (struct RFCNB_Pkt *)RFCNB_Alloc_Pkt(pkt_len);

        if (pkt == NULL) {

            SMBlib_errno = SMBlibE_NoSpace;
            return(SMBlibE_BAD); /* Should handle the error */

        }

        memset(SMB_Hdr(pkt), 0, SMB_ssetpLM_len);
        SIVAL(SMB_Hdr(pkt), SMB_hdr_idf_offset, SMB_DEF_IDF);  /* Plunk in IDF */
        *(SMB_Hdr(pkt) + SMB_hdr_com_offset) = SMBsesssetupX;
        SSVAL(SMB_Hdr(pkt), SMB_hdr_pid_offset, Con_Handle -> pid);
        SSVAL(SMB_Hdr(pkt), SMB_hdr_tid_offset, 0);
        SSVAL(SMB_Hdr(pkt), SMB_hdr_mid_offset, Con_Handle -> mid);
        SSVAL(SMB_Hdr(pkt), SMB_hdr_uid_offset, Con_Handle -> uid);
        *(SMB_Hdr(pkt) + SMB_hdr_wct_offset) = 10;
        *(SMB_Hdr(pkt) + SMB_hdr_axc_offset) = 0xFF;    /* No extra command */
        SSVAL(SMB_Hdr(pkt), SMB_hdr_axo_offset, 0);

        SSVAL(SMB_Hdr(pkt), SMB_ssetpLM_mbs_offset, SMBLIB_MAX_XMIT);
        SSVAL(SMB_Hdr(pkt), SMB_ssetpLM_mmc_offset, 2);
        SSVAL(SMB_Hdr(pkt), SMB_ssetpLM_vcn_offset, Con_Handle -> pid);
        SIVAL(SMB_Hdr(pkt), SMB_ssetpLM_snk_offset, 0);
        SSVAL(SMB_Hdr(pkt), SMB_ssetpLM_pwl_offset, pass_len + 1);
        SIVAL(SMB_Hdr(pkt), SMB_ssetpLM_res_offset, 0);
        SSVAL(SMB_Hdr(pkt), SMB_ssetpLM_bcc_offset, param_len);

        /* Now copy the param strings in with the right stuff */

        p = (char *)(SMB_Hdr(pkt) + SMB_ssetpLM_buf_offset);

        /* Copy  in password, then the rest. Password has a null at end */

        memcpy(p, pword, pass_len);

        p = p + pass_len + 1;

        strcpy(p, UserName);
        p = p + strlen(UserName);
        *p = 0;

        p = p + 1;

        if (NtDomain == NULL) {
            strcpy(p, Con_Handle -> PDomain);
            p = p + strlen(Con_Handle -> PDomain);
        } else {
            strcpy(p, NtDomain);
            p = p + strlen(NtDomain);
        }
        *p = 0;
        p = p + 1;

        strcpy(p, Con_Handle -> OSName);
        p = p + strlen(Con_Handle -> OSName);
        *p = 0;

    } else {

        /* We don't admit to UNICODE support ... */

        param_len = strlen(UserName) + 1 + pass_len +
                    strlen(Con_Handle -> PDomain) + 1 +
                    strlen(Con_Handle -> OSName) + 1 +
                    strlen(Con_Handle -> LMType) + 1;

        pkt_len = SMB_ssetpNTLM_len + param_len;

        pkt = (struct RFCNB_Pkt *)RFCNB_Alloc_Pkt(pkt_len);

        if (pkt == NULL) {

            SMBlib_errno = SMBlibE_NoSpace;
            return(-1); /* Should handle the error */

        }

        memset(SMB_Hdr(pkt), 0, SMB_ssetpNTLM_len);
        SIVAL(SMB_Hdr(pkt), SMB_hdr_idf_offset, SMB_DEF_IDF);  /* Plunk in IDF */
        *(SMB_Hdr(pkt) + SMB_hdr_com_offset) = SMBsesssetupX;
        SSVAL(SMB_Hdr(pkt), SMB_hdr_pid_offset, Con_Handle -> pid);
        SSVAL(SMB_Hdr(pkt), SMB_hdr_tid_offset, 0);
        SSVAL(SMB_Hdr(pkt), SMB_hdr_mid_offset, Con_Handle -> mid);
        SSVAL(SMB_Hdr(pkt), SMB_hdr_uid_offset, Con_Handle -> uid);
        *(SMB_Hdr(pkt) + SMB_hdr_wct_offset) = 13;
        *(SMB_Hdr(pkt) + SMB_hdr_axc_offset) = 0xFF;    /* No extra command */
        SSVAL(SMB_Hdr(pkt), SMB_hdr_axo_offset, 0);

        SSVAL(SMB_Hdr(pkt), SMB_ssetpNTLM_mbs_offset, SMBLIB_MAX_XMIT);
        SSVAL(SMB_Hdr(pkt), SMB_ssetpNTLM_mmc_offset, 0);
        SSVAL(SMB_Hdr(pkt), SMB_ssetpNTLM_vcn_offset, 1); /* Thanks Tridge! */
        SIVAL(SMB_Hdr(pkt), SMB_ssetpNTLM_snk_offset, 0);
        SSVAL(SMB_Hdr(pkt), SMB_ssetpNTLM_cipl_offset, pass_len);
        SSVAL(SMB_Hdr(pkt), SMB_ssetpNTLM_cspl_offset, 0);
        SIVAL(SMB_Hdr(pkt), SMB_ssetpNTLM_res_offset, 0);
        SIVAL(SMB_Hdr(pkt), SMB_ssetpNTLM_cap_offset, 0);
        SSVAL(SMB_Hdr(pkt), SMB_ssetpNTLM_bcc_offset, param_len);

        /* Now copy the param strings in with the right stuff */

        p = (char *)(SMB_Hdr(pkt) + SMB_ssetpNTLM_buf_offset);

        /* Copy  in password, then the rest. Password has no null at end */

        memcpy(p, pword, pass_len);

        p = p + pass_len;

        strcpy(p, UserName);
        p = p + strlen(UserName);
        *p = 0;

        p = p + 1;

        strcpy(p, Con_Handle -> PDomain);
        p = p + strlen(Con_Handle -> PDomain);
        *p = 0;
        p = p + 1;

        strcpy(p, Con_Handle -> OSName);
        p = p + strlen(Con_Handle -> OSName);
        *p = 0;
        p = p + 1;

        strcpy(p, Con_Handle -> LMType);
        p = p + strlen(Con_Handle -> LMType);
        *p = 0;

    }

    /* Now send it and get a response */

    if (RFCNB_Send(Con_Handle -> Trans_Connect, pkt, pkt_len) < 0) {

#ifdef DEBUG
        fprintf(stderr, "Error sending SessSetupX request\n");
#endif

        RFCNB_Free_Pkt(pkt);
        SMBlib_errno = SMBlibE_SendFailed;
        return(SMBlibE_BAD);

    }

    /* Now get the response ... */

    if (RFCNB_Recv(Con_Handle -> Trans_Connect, pkt, pkt_len) < 0) {

#ifdef DEBUG
        fprintf(stderr, "Error receiving response to SessSetupAndX\n");
#endif

        RFCNB_Free_Pkt(pkt);
        SMBlib_errno = SMBlibE_RecvFailed;
        return(SMBlibE_BAD);

    }

    /* Check out the response type ... */

    if (CVAL(SMB_Hdr(pkt), SMB_hdr_rcls_offset) != SMBC_SUCCESS) {  /* Process error */

#ifdef DEBUG
        fprintf(stderr, "SMB_SessSetupAndX failed with errorclass = %i, Error Code = %i\n",
                CVAL(SMB_Hdr(pkt), SMB_hdr_rcls_offset),
                SVAL(SMB_Hdr(pkt), SMB_hdr_err_offset));
#endif

        SMBlib_SMB_Error = IVAL(SMB_Hdr(pkt), SMB_hdr_rcls_offset);
        RFCNB_Free_Pkt(pkt);
        SMBlib_errno = SMBlibE_Remote;
        return(SMBlibE_BAD);

    }

    /** @@@ mdz: check for guest login { **/
    if (SVAL(SMB_Hdr(pkt), SMB_ssetpr_act_offset) & 0x1) {
        /* do we allow guest login? NO! */
        return (SMBlibE_BAD);
    }
    /** @@@ mdz: } **/

#ifdef DEBUG
    fprintf(stderr, "SessSetupAndX response. Action = %i\n",
            SVAL(SMB_Hdr(pkt), SMB_ssetpr_act_offset));
#endif

    /* Now pick up the UID for future reference ... */

    Con_Handle -> uid = SVAL(SMB_Hdr(pkt), SMB_hdr_uid_offset);
    RFCNB_Free_Pkt(pkt);

    return(0);

}