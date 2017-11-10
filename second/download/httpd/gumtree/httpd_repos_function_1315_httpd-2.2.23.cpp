static void format_byte_out(request_rec *r, apr_off_t bytes)
{
    if (bytes < (5 * KBYTE))
        ap_rprintf(r, "%d B", (int) bytes);
    else if (bytes < (MBYTE / 2))
        ap_rprintf(r, "%.1f kB", (float) bytes / KBYTE);
    else if (bytes < (GBYTE / 2))
        ap_rprintf(r, "%.1f MB", (float) bytes / MBYTE);
    else
        ap_rprintf(r, "%.1f GB", (float) bytes / GBYTE);
}