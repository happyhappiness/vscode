int waitpid(pid_t pid, int *statusp, int options)
{
    int tmp_pid;
    if (kill(pid, 0) == -1) {
        errno = ECHILD;
        return -1;
    }
    while (((tmp_pid = wait3(statusp, options, 0)) != pid) &&
                (tmp_pid != -1) && (tmp_pid != 0) && (pid != -1))
        ;
    return tmp_pid;
}