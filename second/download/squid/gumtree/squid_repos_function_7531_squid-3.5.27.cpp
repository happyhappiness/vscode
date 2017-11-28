void *
RFCNB_Call(char *Called_Name, char *Calling_Name, char *Called_Address, int port)
{
    struct RFCNB_Con *con;
    struct in_addr Dest_IP;
    int Client;
    BOOL redirect;
    struct redirect_addr *redir_addr;
    char *Service_Address;

    /* Now, we really should look up the port in /etc/services ... */

    if (port == 0)
        port = RFCNB_Default_Port;

    /* Create a connection structure first */

    if ((con = (struct RFCNB_Con *) malloc(sizeof(struct RFCNB_Con))) == NULL) {        /* Error in size */

        RFCNB_errno = RFCNBE_NoSpace;
        RFCNB_saved_errno = errno;
        return (NULL);

    }
    con->fd = -0;               /* no descriptor yet */
    con->errn = 0;              /* no error yet */
    con->timeout = 0;           /* no timeout   */
    con->redirects = 0;
    con->redirect_list = con->last_addr = NULL;

    /* Resolve that name into an IP address */

    Service_Address = Called_Name;
    if (strlen(Called_Address) != 0) {      /* If the Called Address = "" */
        Service_Address = Called_Address;
    }
    if ((errno = RFCNB_Name_To_IP(Service_Address, &Dest_IP)) < 0) {    /* Error */

        /* No need to modify RFCNB_errno as it was done by RFCNB_Name_To_IP */
        free(con);
        return (NULL);

    }
    /* Now connect to the remote end */

    redirect = TRUE;            /* Fudge this one so we go once through */

    while (redirect) {          /* Connect and get session info etc */

        redirect = FALSE;       /* Assume all OK */

        /* Build the redirect info. First one is first addr called */
        /* And tack it onto the list of addresses we called        */

        if ((redir_addr = (struct redirect_addr *) malloc(sizeof(struct redirect_addr))) == NULL) {     /* Could not get space */

            RFCNB_errno = RFCNBE_NoSpace;
            RFCNB_saved_errno = errno;
            free(con);
            return (NULL);

        }
        memcpy((char *) &(redir_addr->ip_addr), (char *) &Dest_IP, sizeof(Dest_IP));
        redir_addr->port = port;
        redir_addr->next = NULL;

        if (con->redirect_list == NULL) {       /* Stick on head */

            con->redirect_list = con->last_addr = redir_addr;

        } else {

            con->last_addr->next = redir_addr;
            con->last_addr = redir_addr;

        }

        /* Now, make that connection */

        if ((Client = RFCNB_IP_Connect(Dest_IP, port)) < 0) {   /* Error */

            /* No need to modify RFCNB_errno as it was done by RFCNB_IP_Connect */
            free(con);
            return (NULL);

        }
        con->fd = Client;

        /* Now send and handle the RFCNB session request              */
        /* If we get a redirect, we will comeback with redirect true
         * and a new IP address in DEST_IP                            */

        if ((errno = RFCNB_Session_Req(con,
                                       Called_Name,
                                       Calling_Name,
                                       &redirect, &Dest_IP, &port)) < 0) {

            /* No need to modify RFCNB_errno as it was done by RFCNB_Session.. */

            RFCNB_Close(con->fd);       /* Close it */
            free(con);
            return (NULL);

        }
        if (redirect) {

            /* We have to close the connection, and then try again */

            (con->redirects)++;

            RFCNB_Close(con->fd);       /* Close it */

        }
    }

    return (con);
}