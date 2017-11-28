static int
passwd_auth(char *user, char *passwd)
{
    struct passwd *pwd;
    pwd = getpwnam(user);
    if (pwd == NULL) {
        return 0;		/* User does not exist */
    } else {
        if (strcmp(pwd->pw_passwd, (char *) crypt(passwd, pwd->pw_passwd))) {
            return 2;		/* Wrong password */
        } else {
            return 1;		/* Authentication Sucessful */
        }
    }
}