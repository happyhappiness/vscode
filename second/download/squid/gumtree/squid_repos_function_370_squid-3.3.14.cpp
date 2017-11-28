int
Read_allowusers(void)
{
    if (!init) {
        memset(&AllowUsers, '\0', sizeof(AllowUsers));
        init = 1;
    }
    if (*Allowuserpath)
        return Read_usersfile(Allowuserpath, &AllowUsers);
    else
        return 0;
}