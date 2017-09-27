 *   scoreboard shm handle [to recreate the ap_scoreboard]
 */
void get_handles_from_parent(server_rec *s, HANDLE *child_exit_event,
                             apr_proc_mutex_t **child_start_mutex,
                             apr_shm_t **scoreboard_shm)
{
    HANDLE pipe;
    HANDLE hScore;
    HANDLE ready_event;
    HANDLE os_start;
    DWORD BytesRead;
    void *sb_shared;
    apr_status_t rv;

    pipe = GetStdHandle(STD_INPUT_HANDLE);
    if (!ReadFile(pipe, &ready_event, sizeof(HANDLE),
                  &BytesRead, (LPOVERLAPPED) NULL)
        || (BytesRead != sizeof(HANDLE))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Child %d: Unable to retrieve the ready event from the parent", my_pid);
        exit(APEXIT_CHILDINIT);
