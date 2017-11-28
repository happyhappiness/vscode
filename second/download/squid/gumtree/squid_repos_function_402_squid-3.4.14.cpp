static int
QueryServerForUser(int x, char *username, char *password)
{
    int result = 1;

    result = Valid_User(username, password, ServerArray[x].pdc,
                        ServerArray[x].bdc, ServerArray[x].domain);

    switch (result) {		/* Write any helpful syslog messages */
    case 0:
        break;
    case 1:
        syslog(LOG_AUTHPRIV | LOG_INFO, "Server error when checking %s.",
               username);
        break;
    case 2:
        syslog(LOG_AUTHPRIV | LOG_INFO, "Protocol error when checking %s.",
               username);
        break;
    case 3:
        syslog(LOG_AUTHPRIV | LOG_INFO, "Authentication failed for %s.",
               username);
        break;
    }

    return result;
}