 */

#include "apr_arch_threadproc.h"

APR_DECLARE(apr_status_t) apr_proc_detach(int daemonize)
{
    if (chdir("/") == -1) {
        return errno;
    }

#if !defined(MPE) && !defined(OS2) && !defined(TPF) && !defined(BEOS)
    /* Don't detach for MPE because child processes can't survive the death of
     * the parent. */
    if (daemonize) {
        int x;

        if ((x = fork()) > 0) {
            exit(0);
        }
        else if (x == -1) {
            perror("fork");
            fprintf(stderr, "unable to fork new process\n");
