static void show_time(request_rec *r, apr_uint32_t tsecs)
{
    int days, hrs, mins, secs;

    secs = (int)(tsecs % 60);
    tsecs /= 60;
    mins = (int)(tsecs % 60);
    tsecs /= 60;
    hrs = (int)(tsecs % 24);
    days = (int)(tsecs / 24);

    if (days)
        ap_rprintf(r, " %d day%s", days, days == 1 ? "" : "s");

    if (hrs)
        ap_rprintf(r, " %d hour%s", hrs, hrs == 1 ? "" : "s");

    if (mins)
        ap_rprintf(r, " %d minute%s", mins, mins == 1 ? "" : "s");

    if (secs)
        ap_rprintf(r, " %d second%s", secs, secs == 1 ? "" : "s");
}