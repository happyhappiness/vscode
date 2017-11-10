static unsigned is_absolute_uri(char *uri, int *supportsqs)
{
    int dummy, *sqs;

    sqs = (supportsqs ? supportsqs : &dummy);
    *sqs = 0;
    /* fast exit */
    if (*uri == '/' || strlen(uri) <= 5) {
        return 0;
    }

    switch (*uri++) {
    case 'a':
    case 'A':
        if (!strncasecmp(uri, "jp://", 5)) {        /* ajp://    */
          *sqs = 1;
          return 6;
        }
        break;

    case 'b':
    case 'B':
        if (!strncasecmp(uri, "alancer://", 10)) {   /* balancer:// */
          *sqs = 1;
          return 11;
        }
        break;

    case 'f':
    case 'F':
        if (!strncasecmp(uri, "tp://", 5)) {        /* ftp://    */
            return 6;
        }
        if (!strncasecmp(uri, "cgi://", 6)) {       /* fcgi://   */
            *sqs = 1;
            return 7;
        }
        break;

    case 'g':
    case 'G':
        if (!strncasecmp(uri, "opher://", 8)) {     /* gopher:// */
            return 9;
        }
        break;

    case 'h':
    case 'H':
        if (!strncasecmp(uri, "ttp://", 6)) {       /* http://   */
            *sqs = 1;
            return 7;
        }
        else if (!strncasecmp(uri, "ttps://", 7)) { /* https://  */
            *sqs = 1;
            return 8;
        }
        break;

    case 'l':
    case 'L':
        if (!strncasecmp(uri, "dap://", 6)) {       /* ldap://   */
            return 7;
        }
        break;

    case 'm':
    case 'M':
        if (!strncasecmp(uri, "ailto:", 6)) {       /* mailto:   */
            *sqs = 1;
            return 7;
        }
        break;

    case 'n':
    case 'N':
        if (!strncasecmp(uri, "ews:", 4)) {         /* news:     */
            return 5;
        }
        else if (!strncasecmp(uri, "ntp://", 6)) {  /* nntp://   */
            return 7;
        }
        break;

    case 's':
    case 'S':
        if (!strncasecmp(uri, "cgi://", 6)) {       /* scgi://   */
            *sqs = 1;
            return 7;
        }
        break;
    }

    return 0;
}