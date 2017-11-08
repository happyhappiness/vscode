static void htdbm_usage(void)
{

#if (!(defined(WIN32) || defined(NETWARE)))
#define CRYPT_OPTION "d"
#else
#define CRYPT_OPTION ""
#endif
    fprintf(stderr, "htdbm -- program for manipulating DBM password databases.\n\n");
    fprintf(stderr, "Usage: htdbm    [-cm"CRYPT_OPTION"pstvx] [-TDBTYPE] database username\n");
    fprintf(stderr, "                -b[cm"CRYPT_OPTION"ptsv] [-TDBTYPE] database username password\n");
    fprintf(stderr, "                -n[m"CRYPT_OPTION"pst]   username\n");
    fprintf(stderr, "                -nb[m"CRYPT_OPTION"pst]  username password\n");
    fprintf(stderr, "                -v[m"CRYPT_OPTION"ps]    [-TDBTYPE] database username\n");
    fprintf(stderr, "                -vb[m"CRYPT_OPTION"ps]   [-TDBTYPE] database username password\n");
    fprintf(stderr, "                -x[m"CRYPT_OPTION"ps]    [-TDBTYPE] database username\n");
    fprintf(stderr, "                -l                       [-TDBTYPE] database\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "   -b   Use the password from the command line rather "
                    "than prompting for it.\n");
    fprintf(stderr, "   -c   Create a new database.\n");
    fprintf(stderr, "   -n   Don't update database; display results on stdout.\n");
    fprintf(stderr, "   -m   Force MD5 encryption of the password (default).\n");
#if (!(defined(WIN32) || defined(NETWARE)))
    fprintf(stderr, "   -d   Force CRYPT encryption of the password (now deprecated).\n");
#endif
    fprintf(stderr, "   -p   Do not encrypt the password (plaintext).\n");
    fprintf(stderr, "   -s   Force SHA encryption of the password.\n");
    fprintf(stderr, "   -T   DBM Type (SDBM|GDBM|DB|default).\n");
    fprintf(stderr, "   -l   Display usernames from database on stdout.\n");
    fprintf(stderr, "   -t   The last param is username comment.\n");
    fprintf(stderr, "   -v   Verify the username/password.\n");
    fprintf(stderr, "   -x   Remove the username record from database.\n");
    exit(ERR_SYNTAX);

}