SMB_Handle_Type SMB_Connect_Server(SMB_Handle_Type Con_Handle,
                                   const char *server, const char *NTdomain)

{
    SMB_Handle_Type con;
    char called[80], calling[80], *address;
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

    strcpy(con -> service, "");
    strcpy(con -> username, "");
    strcpy(con -> password, "");
    strcpy(con -> sock_options, "");
    strcpy(con -> address, "");
    strncpy(con -> desthost, server, sizeof(con->desthost));
    con->desthost[sizeof(con->desthost) - 1] = '\0';
    strncpy(con -> PDomain, NTdomain, sizeof(con->PDomain));
    con->PDomain[sizeof(con->PDomain) - 1] = '\0';
    strcpy(con -> OSName, SMBLIB_DEFAULT_OSNAME);
    strcpy(con -> LMType, SMBLIB_DEFAULT_LMTYPE);
    con -> first_tree = con -> last_tree = NULL;

    SMB_Get_My_Name(con -> myname, sizeof(con -> myname));

    con -> port = 0;                    /* No port selected */

    /* Get some things we need for the SMB Header */

    con -> pid = getpid();
    con -> mid = con -> pid;      /* This will do for now ... */
    con -> uid = 0;               /* Until we have done a logon, no uid ... */
    con -> gid = getgid();

    /* Now connect to the remote end, but first upper case the name of the
       service we are going to call, sine some servers want it in uppercase */

    for (i=0; i < strlen(server); i++)
        called[i] = xtoupper(server[i]);

    called[strlen(server)] = 0;    /* Make it a string */

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
            Con_Handle = NULL;
            free(con);
        }
        SMBlib_errno = -SMBlibE_CallFailed;
        return NULL;

    }

    return(con);

}