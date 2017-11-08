int main(int argc, char *argv[])
{
    int userdir = 0;        /* ~userdir flag             */
    uid_t uid;              /* user information          */
    gid_t gid;              /* target group placeholder  */
    char *target_uname;     /* target user name          */
    char *target_gname;     /* target group name         */
    char *target_homedir;   /* target home directory     */
    char *actual_uname;     /* actual user name          */
    char *actual_gname;     /* actual group name         */
    char *cmd;              /* command to be executed    */
    char cwd[AP_MAXPATH];   /* current working directory */
    char dwd[AP_MAXPATH];   /* docroot working directory */
    struct passwd *pw;      /* password entry holder     */
    struct group *gr;       /* group entry holder        */
    struct stat dir_info;   /* directory info holder     */
    struct stat prg_info;   /* program info holder       */

    /*
     * Start with a "clean" environment
     */
    clean_env();

    /*
     * Check existence/validity of the UID of the user
     * running this program.  Error out if invalid.
     */
    uid = getuid();
    if ((pw = getpwuid(uid)) == NULL) {
        log_err("crit: invalid uid: (%ld)\n", uid);
        exit(102);
    }
    /*
     * See if this is a 'how were you compiled' request, and
     * comply if so.
     */
    if ((argc > 1)
        && (! strcmp(argv[1], "-V"))
        && ((uid == 0)
#ifdef _OSD_POSIX
        /* User name comparisons are case insensitive on BS2000/OSD */
            || (! strcasecmp(AP_HTTPD_USER, pw->pw_name)))
#else  /* _OSD_POSIX */
            || (! strcmp(AP_HTTPD_USER, pw->pw_name)))
#endif /* _OSD_POSIX */
        ) {
#ifdef AP_DOC_ROOT
        fprintf(stderr, " -D AP_DOC_ROOT=\"%s\"\n", AP_DOC_ROOT);
#endif
#ifdef AP_GID_MIN
        fprintf(stderr, " -D AP_GID_MIN=%d\n", AP_GID_MIN);
#endif
#ifdef AP_HTTPD_USER
        fprintf(stderr, " -D AP_HTTPD_USER=\"%s\"\n", AP_HTTPD_USER);
#endif
#ifdef AP_LOG_EXEC
        fprintf(stderr, " -D AP_LOG_EXEC=\"%s\"\n", AP_LOG_EXEC);
#endif
#ifdef AP_SAFE_PATH
        fprintf(stderr, " -D AP_SAFE_PATH=\"%s\"\n", AP_SAFE_PATH);
#endif
#ifdef AP_SUEXEC_UMASK
        fprintf(stderr, " -D AP_SUEXEC_UMASK=%03o\n", AP_SUEXEC_UMASK);
#endif
#ifdef AP_UID_MIN
        fprintf(stderr, " -D AP_UID_MIN=%d\n", AP_UID_MIN);
#endif
#ifdef AP_USERDIR_SUFFIX
        fprintf(stderr, " -D AP_USERDIR_SUFFIX=\"%s\"\n", AP_USERDIR_SUFFIX);
#endif
        exit(0);
    }