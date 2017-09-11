/* =========================== Events notification ========================== */

void sentinelCallNotificationScript(char *scriptpath, char *type, char *msg) {
    pid_t pid = fork();

    if (pid == -1) {
        /* Parent on error. */
        sentinelEvent(REDIS_WARNING,"-notification-script-error",NULL,
                      "#can't fork: %s",strerror(errno));
        return;
    } else if (pid == 0) {
        /* Child */
        char *argv[4];

        argv[0] = scriptpath;
        argv[1] = type;
        argv[2] = msg;
        argv[3] = NULL;
        execve(scriptpath,argv,environ);
        /* If we are here an error occurred. */
        sentinelEvent(REDIS_WARNING,"-notification-script-error",NULL,
                      "#execve(2): %s",strerror(errno));
        _exit(1);
    } else {
        sentinelEvent(REDIS_DEBUG,"+child",NULL,"%ld",(long)pid);
    }
}

/* Send an event to log, pub/sub, user notification script.
