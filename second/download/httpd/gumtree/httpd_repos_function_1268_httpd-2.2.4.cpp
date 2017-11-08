static void format_kbyte_out(request_rec *r, apr_off_t kbytes)
{
    if (kbytes < KBYTE)
        ap_rprintf(r, "%d kB", (int) kbytes);
    else if (kbytes < MBYTE)
        ap_rprintf(r, "%.1f MB", (float) kbytes / KBYTE);
    else
        ap_rprintf(r, "%.1f GB", (float) kbytes / MBYTE);
}