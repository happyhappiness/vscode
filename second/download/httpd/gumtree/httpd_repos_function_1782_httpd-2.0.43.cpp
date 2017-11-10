void ap_time_process_request(int child_num, int thread_num, int status)
{
    worker_score *ws;

    if (child_num < 0) {
        return;
    }

    ws = &ap_scoreboard_image->servers[child_num][thread_num];

    if (status == START_PREQUEST) {
        ws->start_time = apr_time_now(); 
    }
    else if (status == STOP_PREQUEST) {
        ws->stop_time = apr_time_now(); 
    }
}