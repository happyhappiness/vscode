static void logmsg(const char *msg)
{
    time_t t = time(NULL);
    struct tm *curr_time = localtime(&t);
    char loctime[80];

    strcpy(loctime, asctime(curr_time));
    loctime[strlen(loctime) - 1] = '\0';
    fprintf(logfp, "%s: %d: %s\n", loctime, (int)getpid(), msg);
    fflush(logfp);
}