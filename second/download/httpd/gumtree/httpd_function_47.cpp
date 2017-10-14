static char *getpass(const char *prompt)
{
/* WCE lacks console. So the getpass is unsuported
 * The only way is to use the GUI so the getpass should be implemented
 * on per-application basis.
*/ 
#ifdef _WIN32_WCE
    return NULL;
#else
    static char password[MAX_STRING_LEN];
    int n = 0;

    fputs(prompt, stderr);
    
    while ((password[n] = _getch()) != '\r') {
        if (n < sizeof(password) - 1 && password[n] >= ' ' && password[n] <= '~') {
            n++;
            printf("*");
        }
	else {
            printf("\n");
            fputs(prompt, stderr);
            n = 0;
        }
    }
 
    password[n] = '\0';
    printf("\n");

    if (n > (MAX_STRING_LEN - 1)) {
        password[MAX_STRING_LEN - 1] = '\0';
    }

    return (char *) &password;
#endif
}