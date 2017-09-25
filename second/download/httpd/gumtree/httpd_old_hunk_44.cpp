

AP_DECLARE(int) ap_mpm_run(apr_pool_t *_pconf, apr_pool_t *plog, server_rec *s )
{
    static int restart = 0;            /* Default is "not a restart" */

    /* ### If non-graceful restarts are ever introduced - we need to rerun 
     * the pre_mpm hook on subsequent non-graceful restarts.  But Win32 
     * has only graceful style restarts - and we need this hook to act 
     * the same on Win32 as on Unix.
     */
    if (!restart && ((parent_pid == my_pid) || one_process)) {
