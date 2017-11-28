int
Check_ifuserallowed(char *ConnectingUser)
{
    return Check_userlist(&AllowUsers, ConnectingUser);
}