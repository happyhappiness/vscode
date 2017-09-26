        return -1;
    if ((a->waittime) > (b->waittime))
        return 1;
    return 0;
}

static void output_results(void)
{
    apr_interval_time_t timetakenusec;
    float timetaken;

    endtime = apr_time_now();
    timetakenusec = endtime - start;
    timetaken = ((float)apr_time_sec(timetakenusec)) +
        ((float)apr_time_usec(timetakenusec)) / 1000000.0F;

    printf("\n\n");
    printf("Server Software:        %s\n", servername);
    printf("Server Hostname:        %s\n", hostname);
    printf("Server Port:            %hu\n", port);
#ifdef USE_SSL
