            ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf,
                         "select/accept error (%d)", status);
            return APR_EGENERAL;
#else
        default:
            ap_log_error(APLOG_MARK, APLOG_ERR, status, ap_server_conf,
                         "apr_socket_accept: (client socket)");
            return APR_EGENERAL;
#endif
    }
    return status;
}


#ifdef _OSD_POSIX

#include "apr_lib.h"

#define USER_LEN 8

typedef enum
{
    bs2_unknown,     /* not initialized yet. */
    bs2_noFORK,      /* no fork() because -X flag was specified */
    bs2_FORK,        /* only fork() because uid != 0 */
    bs2_UFORK        /* Normally, ufork() is used to switch identities. */
} bs2_ForkType;

static bs2_ForkType forktype = bs2_unknown;


static void ap_str_toupper(char *str)
{
    while (*str) {
        *str = apr_toupper(*str);
        ++str;
    }
}

/* Determine the method for forking off a child in such a way as to
 * set both the POSIX and BS2000 user id's to the unprivileged user.
 */
static bs2_ForkType os_forktype(int one_process)
{
    /* have we checked the OS version before? If yes return the previous
     * result - the OS release isn't going to change suddenly!
     */
    if (forktype == bs2_unknown) {
        /* not initialized yet */

        /* No fork if the one_process option was set */
        if (one_process) {
            forktype = bs2_noFORK;
        }
        /* If the user is unprivileged, use the normal fork() only. */
        else if (getuid() != 0) {
            forktype = bs2_FORK;
        }
        else
            forktype = bs2_UFORK;
    }
    return forktype;
}



/* This routine complements the setuid() call: it causes the BS2000 job
 * environment to be switched to the target user's user id.
 * That is important if CGI scripts try to execute native BS2000 commands.
 */
int os_init_job_environment(server_rec *server, const char *user_name, int one_process)
{
    bs2_ForkType            type = os_forktype(one_process);

    /* We can be sure that no change to uid==0 is possible because of
     * the checks in http_core.c:set_user()
     */

    if (one_process) {

        type = forktype = bs2_noFORK;

        ap_log_error(APLOG_MARK, APLOG_ERR, 0, server,
                     "The debug mode of Apache should only "
                     "be started by an unprivileged user!");
        return 0;
    }

    return 0;
}

/* BS2000 requires a "special" version of fork() before a setuid() call */
pid_t os_fork(const char *user)
{
    pid_t pid;
    char  username[USER_LEN+1];

    switch (os_forktype(0)) {

      case bs2_FORK:
        pid = fork();
        break;

      case bs2_UFORK:
        apr_cpystrn(username, user, sizeof username);

        /* Make user name all upper case - for some versions of ufork() */
        ap_str_toupper(username);

        pid = ufork(username);
        if (pid == -1 && errno == EPERM) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, errno,
                         NULL, "ufork: Possible mis-configuration "
                         "for user %s - Aborting.", user);
            exit(1);
        }
        break;

      default:
        pid = 0;
        break;
    }

    return pid;
}

#endif /* _OSD_POSIX */

