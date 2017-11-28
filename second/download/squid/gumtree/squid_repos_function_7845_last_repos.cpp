void
nt_lm_owf_gen(char *pwd, char *nt_p16, char *p16)
{
    char passwd[130];
    StrnCpy(passwd, pwd, sizeof(passwd) - 1);

    /* Calculate the MD4 hash (NT compatible) of the password */
    memset(nt_p16, '\0', 16);
    E_md4hash((uchar *) passwd, (uchar *) nt_p16);

    /* Mangle the passwords into Lanman format */
    passwd[14] = '\0';
    strupper(passwd);

    /* Calculate the SMB (lanman) hash functions of the password */

    memset(p16, '\0', 16);
    E_P16((uchar *) passwd, (uchar *) p16);

    /* clear out local copy of user's password (just being paranoid). */
    memset(passwd, 0, sizeof(passwd));
}