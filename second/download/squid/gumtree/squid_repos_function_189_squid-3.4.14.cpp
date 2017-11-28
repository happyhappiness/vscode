int
match_user(char *dict_username, char *username)
{
    if ((strcmp(dict_username, username)) == 0) {
        return 1;
    } else {
        if ((strcmp(dict_username, "ALL")) == 0) {
            return 1;
        }
    }
    return 0;
}