int
Check_user(char *ConnectingUser)
{
    if (Check_ifuserdenied(ConnectingUser) == 1)
        return 1;

    if (Check_ifuserallowed(ConnectingUser) == 0)
        return 1;

    return 0;
}