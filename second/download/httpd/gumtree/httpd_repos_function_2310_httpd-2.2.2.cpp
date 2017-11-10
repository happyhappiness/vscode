static void display_settings ()
{
    int status_array[SERVER_NUM_STATUS];
    int i, status, total=0;
    int reqs = request_count;
#ifdef DBINFO_ON
    int wblock = would_block;

    would_block = 0;
#endif

    request_count = 0;

    ClearScreen (getscreenhandle());
    printf("%s \n", ap_get_server_version());

    for (i=0;i<SERVER_NUM_STATUS;i++) {
        status_array[i] = 0;
    }

    for (i = 0; i < ap_threads_limit; ++i) {
        status = (ap_scoreboard_image->servers[0][i]).status;
        status_array[status]++;
    }

    for (i=0;i<SERVER_NUM_STATUS;i++) {
        switch(i)
        {
        case SERVER_DEAD:
            printf ("Available:\t%d\n", status_array[i]);
            break;
        case SERVER_STARTING:
            printf ("Starting:\t%d\n", status_array[i]);
            break;
        case SERVER_READY:
            printf ("Ready:\t\t%d\n", status_array[i]);
            break;
        case SERVER_BUSY_READ:
            printf ("Busy:\t\t%d\n", status_array[i]);
            break;
        case SERVER_BUSY_WRITE:
            printf ("Busy Write:\t%d\n", status_array[i]);
            break;
        case SERVER_BUSY_KEEPALIVE:
            printf ("Busy Keepalive:\t%d\n", status_array[i]);
            break;
        case SERVER_BUSY_LOG:
            printf ("Busy Log:\t%d\n", status_array[i]);
            break;
        case SERVER_BUSY_DNS:
            printf ("Busy DNS:\t%d\n", status_array[i]);
            break;
        case SERVER_CLOSING:
            printf ("Closing:\t%d\n", status_array[i]);
            break;
        case SERVER_GRACEFUL:
            printf ("Restart:\t%d\n", status_array[i]);
            break;
        case SERVER_IDLE_KILL:
            printf ("Idle Kill:\t%d\n", status_array[i]);
            break;
        default:
            printf ("Unknown Status:\t%d\n", status_array[i]);
            break;
        }
        if (i != SERVER_DEAD)
            total+=status_array[i];
    }
    printf ("Total Running:\t%d\tout of: \t%d\n", total, ap_threads_limit);
    printf ("Requests per interval:\t%d\n", reqs);

#ifdef DBINFO_ON
    printf ("Would blocks:\t%d\n", wblock);
    printf ("Successful retries:\t%d\n", retry_success);
    printf ("Failed retries:\t%d\n", retry_fail);
    printf ("Avg retries:\t%d\n", retry_success == 0 ? 0 : avg_retries / retry_success);
#endif
}