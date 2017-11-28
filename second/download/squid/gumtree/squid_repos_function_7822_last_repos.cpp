SMB_Handle_Type SMB_Connect(SMB_Handle_Type Con_Handle,
                            SMB_Tree_Handle *tree,
                            char *service,
                            char *username,
                            char *password)

{
    SMB_Handle_Type con;
    char *host, *address;
    char temp[80], called[80], calling[80];
    int i;

    /* Get a connection structure if one does not exist */

    con = Con_Handle;

    if (Con_Handle == NULL) {

        if ((con = (struct SMB_Connect_Def *)malloc(sizeof(struct SMB_Connect_Def))) == NULL) {

            SMBlib_errno = SMBlibE_NoSpace;
            return NULL;
        }

    }

    /* Init some things ... */

    strncpy(con -> service, service, sizeof(con -> service));
    con -> service[sizeof(con -> service) - 1] = '\0';
    strncpy(con -> username, username, sizeof(con -> username));
    con -> username[sizeof(con -> username) - 1] = '\0';
    strncpy(con -> password, password, sizeof(con -> password));
    con -> password[sizeof(con -> password) - 1] = '\0';
    strcpy(con -> sock_options, "");
    strcpy(con -> address, "");
    strcpy(con -> PDomain, SMBLIB_DEFAULT_DOMAIN);
    strcpy(con -> OSName, SMBLIB_DEFAULT_OSNAME);
    strcpy(con -> LMType, SMBLIB_DEFAULT_LMTYPE);
    con -> first_tree = con -> last_tree = NULL;

    SMB_Get_My_Name(con -> myname, sizeof(con -> myname));

    con -> port = 0;                    /* No port selected */

    /* Get some things we need for the SMB Header */

    con -> pid = getpid();
    con -> mid = con -> pid;      /* This will do for now ... */
    con -> uid = 0;               /* Until we have done a logon, no uid */
    con -> gid = getgid();

    /* Now figure out the host portion of the service */

    strncpy(temp, service, sizeof(temp));
    temp[sizeof(temp) - 1] = '\0';
    host = strtok(temp, "/\\");     /* Separate host name portion */
    if (!host) {
        if (Con_Handle == NULL) {
            free(con);
            Con_Handle = NULL;
        }
        SMBlib_errno = -SMBlibE_CallFailed;
        return NULL;
    }
    strncpy(con->desthost, host, sizeof(con->desthost));
    con->desthost[sizeof(con->desthost)-1]='\0';

    /* Now connect to the remote end, but first upper case the name of the
       service we are going to call, sine some servers want it in uppercase */

    for (i=0; i < strlen(host); i++)
        called[i] = xtoupper(host[i]);

    called[strlen(host)] = 0;    /* Make it a string */

    for (i=0; i < strlen(con -> myname); i++)
        calling[i] = xtoupper(con -> myname[i]);

    calling[strlen(con -> myname)] = 0;    /* Make it a string */

    if (strlen(con -> address) == 0)
        address = con -> desthost;
    else
        address = con -> address;

    con -> Trans_Connect = RFCNB_Call(called,
                                      calling,
                                      address, /* Protocol specific */
                                      con -> port);

    /* Did we get one? */

    if (con -> Trans_Connect == NULL) {

        if (Con_Handle == NULL) {
            free(con);
            Con_Handle = NULL;
        }
        SMBlib_errno = -SMBlibE_CallFailed;
        return NULL;

    }

    /* Now, negotiate the protocol */

    if (SMB_Negotiate(con, SMB_Prots_Restrict) < 0) {

        if (Con_Handle == NULL) {
            free(con);
        }
        SMBlib_errno = -SMBlibE_NegNoProt;
        return NULL;

    }

    /* Now connect to the service ... */

    if ((*tree = SMB_TreeConnect(con, NULL, service, password, "A:")) == NULL) {

        if (Con_Handle == NULL) {
            free(con);
        }
        SMBlib_errno = -SMBlibE_BAD;
        return NULL;

    }

    return(con);

}