void *
NTLM_Connect(char *server, char *backup, char *domain, char *nonce)
{
    char const *SMB_Prots[] = {
        /*              "PC NETWORK PROGRAM 1.0", */
        /*              "MICROSOFT NETWORKS 1.03", */
        /*              "MICROSOFT NETWORKS 3.0", */
        "LANMAN1.0",
        "LM1.2X002",
        "Samba",
        /*              "NT LM 0.12", */
        /*              "NT LANMAN 1.0", */
        NULL
    };
    SMB_Handle_Type con;

    SMB_Init();
    con = SMB_Connect_Server(NULL, server, domain);
    if (con == NULL) {		/* Error ... */
        con = SMB_Connect_Server(NULL, backup, domain);
        if (con == NULL) {
            return (NULL);
        }
    }
    if (SMB_Negotiate(con, SMB_Prots) < 0) {	/* An error */
        SMB_Discon(con, 0);
        return (NULL);
    }
    /* Test for a server in share level mode do not authenticate against it */
    if (con->Security == 0) {
        SMB_Discon(con, 0);
        return (NULL);
    }
    memcpy(nonce, con->Encrypt_Key, 8);

    return (con);
}