SIGRETTYPE
sigChild( int signo )
// purpose: supply ad hoc child handler with output on stderr
// paramtr: signo (IN): == SIGCHLD
// returns: only if OS uses a return type for signal handler
// seealso: Stevens, UNP, figure 5.11 *and* Stevens, APUE, figure 8.3
{
    pid_t pid;
    int  status = signo; // to stop GNU from complaining...

    int saveerr = errno;
    while ( (pid = waitpid( -1, &status, WNOHANG )) > 0 ) {
        if ( WIFEXITED(status) ) {
            fprintf( stderr, "child (pid=%ld) reaped, status %d\n%c",
                     (long) pid, WEXITSTATUS(status), 0 );
        } else if ( WIFSIGNALED(status) ) {
            fprintf( stderr, "child (pid=%ld) died on signal %d%s\n%c",
                     (long) pid, WTERMSIG(status),
#ifdef WCOREDUMP
                     WCOREDUMP(status) ? " (core generated)" : "",
#else
                     "",
#endif
                     0 );
        } else {
            fprintf( stderr, "detected dead child (pid=%ld), status %d\n%c",
                     (long) pid, status, 0 );
        }
    }
    errno = saveerr;

#if SIGRETTYPE != void
    return 0;
#endif
}