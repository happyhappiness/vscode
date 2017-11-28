static int
shadow_auth(char *user, char *passwd)
{
    struct spwd *pwd;
    pwd = getspnam(user);
    if (pwd == NULL) {
        return passwd_auth(user, passwd);	/* Fall back to passwd_auth */
    } else {
        if (strcmp(pwd->sp_pwdp, crypt(passwd, pwd->sp_pwdp))) {
            return 2;		/* Wrong password */
        } else {
            return 1;		/* Authentication Sucessful */
        }
    }
}