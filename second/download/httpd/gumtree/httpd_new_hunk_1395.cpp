    fputs(prompt, stderr);
    fgets((char *) &password, sizeof(password), stdin);

    return (char *) &password;
}

#elif defined(WIN32)

/*
 * Windows lacks getpass().  So we'll re-implement it here.
 */

static char *get_password(const char *prompt)
