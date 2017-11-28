static int
init_challenge(char *domain, char *domain_controller)
{
    int smberr;

    if (handle != NULL) {
        return 0;
    }
    debug("Connecting to server %s domain %s\n", domain_controller, domain);
    handle = SMB_Connect_Server(NULL, domain_controller, domain);
    smberr = SMB_Get_Last_Error();
    SMB_Get_Error_Msg(smberr, errstr, 1000);

    if (handle == NULL) {   /* couldn't connect */
        debug("Couldn't connect to SMB Server. Error:%s\n", errstr);
        return 1;
    }
    if (SMB_Negotiate(handle, SMB_Prots) < 0) {     /* An error */
        debug("Error negotiating protocol with SMB Server\n");
        SMB_Discon(handle, 0);
        handle = NULL;
        return 2;
    }
    if (handle->Security == 0) {    /* share-level security, unuseable */
        debug("SMB Server uses share-level security .. we need user security.\n");
        SMB_Discon(handle, 0);
        handle = NULL;
        return 3;
    }
    memcpy(challenge, handle->Encrypt_Key, NTLM_NONCE_LEN);
    SMBencrypt((unsigned char *)"",challenge,lmencoded_empty_pass);
    SMBNTencrypt((unsigned char *)"",challenge,ntencoded_empty_pass);
    return 0;
}