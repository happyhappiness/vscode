void
BasicUser::extractUsername()
{
    char * seperator = strchr(cleartext, ':');

    if (seperator == NULL) {
        username(cleartext);
    } else {
        /* terminate the username */
        *seperator = '\0';

        username(cleartext);

        /* replace the colon so we can find the password */
        *seperator = ':';
    }

    if (!basicConfig.casesensitive)
        Tolower((char *)username());
}