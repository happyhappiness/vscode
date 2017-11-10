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