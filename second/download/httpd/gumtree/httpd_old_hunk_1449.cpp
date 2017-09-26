    fputc('\n', stderr);
    password[n] = '\0';
    return password;
#endif
}

#endif /* no getchar or _getch */

#endif /* no getpass or getpassphrase or getpass_r */

/*
 * Use the OS getpass() routine (or our own) to obtain a password from
