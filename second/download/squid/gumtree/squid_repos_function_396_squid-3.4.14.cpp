int
Check_userlist(usersfile * uf, char *User)
{
    void *p;

    /* Empty users are always in the list */
    if (User[0] == '\0')
        return 1;

    /* If allowed user list is empty, allow all users.
     * If no users are supposed to be using the proxy, stop squid instead. */
    if (0 == uf->Inuse)
        return 1;

    /* Check if username string is found in the allowed user list.
     * If so, allow. If not, deny. Reconstruct the username
     * to have whitespace, to avoid finding wrong string subsets. */

    p = bsearch(&User,
                uf->names,
                uf->Inuse,
                sizeof(*uf->names),
                name_cmp);
    if (NULL == p) {
        return 0;
    }
    return 1;
}