int
Read_denyusers(void)
{
    if (!init) {
        memset(&DenyUsers, '\0', sizeof(DenyUsers));
        init = 1;
    }
    if (*Denyuserpath)
        return Read_usersfile(Denyuserpath, &DenyUsers);
    else
        return 0;
}