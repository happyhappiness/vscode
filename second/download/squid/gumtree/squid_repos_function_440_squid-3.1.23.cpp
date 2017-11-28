static const user_data *
GetPassword(RequestData * requestData)
{
    user_data *u;
    struct stat sb;
    char buf[256];
    int len;
    if (stat(passwdfile, &sb) == 0) {
        if (sb.st_mtime != change_time) {
            read_passwd_file(passwdfile, ha1mode);
            change_time = sb.st_mtime;
        }
    }
    if (!hash)
        return NULL;
    len = snprintf(buf, sizeof(buf), "%s:%s", requestData->user, requestData->realm);
    if (len >= sizeof(buf))
        return NULL;
    u = (user_data *) hash_lookup(hash, buf);
    if (u)
        return u;
    u = (user_data *) hash_lookup(hash, requestData->user);
    return u;
}