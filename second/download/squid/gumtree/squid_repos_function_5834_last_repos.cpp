static int
shadow_auth(char *user, char *passwd)
{
    struct spwd *pwd;
    pwd = getspnam(user);
    if (pwd == NULL) {
        return passwd_auth(user, passwd);   /* Fall back to passwd_auth */
    } else {
        char *crypted = crypt(passwd, pwd->sp_pwdp);
        if (!crypted || strcmp(pwd->sp_pwdp, crypted)) {
            return 2;       /* Wrong password */
        } else {
            return 1;       /* Authentication Sucessful */
        }
    }
}