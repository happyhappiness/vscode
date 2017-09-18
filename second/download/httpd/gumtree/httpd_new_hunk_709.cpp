
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
