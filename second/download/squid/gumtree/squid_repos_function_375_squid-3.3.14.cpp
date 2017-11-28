static int
Check_ifuserdenied(char *ConnectingUser)
{
    /* If user string is empty, deny */
    if (ConnectingUser[0] == '\0')
        return 1;

    /* If denied user list is empty, allow */
    if (DenyUsers.Inuse == 0)
        return 0;

    return Check_userlist(&DenyUsers, ConnectingUser);
}