static int
passwd_auth(char *user, char *passwd)
{
    struct passwd *pwd;
    pwd = getpwnam(user);
    if (pwd == NULL) {
        return 0;       /* User does not exist */
    } else {
        char *crypted = crypt(passwd, pwd->pw_passwd);
        if (!crypted || strcmp(pwd->pw_passwd, crypted)) {
            return 2;       /* Wrong password */
        } else {
            return 1;       /* Authentication Sucessful */
        }
    }
}