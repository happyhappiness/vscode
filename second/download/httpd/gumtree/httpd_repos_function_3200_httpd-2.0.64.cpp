static char *getpass(const char *prompt)
{
    static char password[MAX_STRING_LEN];

    fputs(prompt, stderr);
    fgets((char *) &password, sizeof(password), stdin);

    return (char *) &password;
}