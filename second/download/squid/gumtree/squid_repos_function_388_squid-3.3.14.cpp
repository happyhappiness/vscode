int
QueryServers(char *username, char *password)
{
    int i;
    for (i = 0; i < Serversqueried; ++i) {
        if (0 == QueryServerForUser(i, username, password))
            return 0;
    }
    return 1;
}