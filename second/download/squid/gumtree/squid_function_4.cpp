static void
xmalloc_show_trace(void *p, int sign)
{
    static double last_accounted = 0;
    static size_t last_total = 0, last_mallinfo = 0;
    double accounted = statMemoryAccounted();
    size_t mi = 0;
    size_t sz;
#if HAVE_MALLINFO

    struct mallinfo mp = mallinfo();
    mi = mp.uordblks + mp.usmblks + mp.hblkhd;
#endif

    sz = xmallocblksize(p) * sign;
    xmalloc_total += sz;
    xmalloc_count += sign > 0;

    if (xmalloc_trace) {
        fprintf(stderr, "%c%8p size=%5d/%d acc=%5.0f/%.0f mallinfo=%5d/%d %s:%d %s",
                sign > 0 ? '+' : '-', p,
                (int) xmalloc_total - last_total, (int) xmalloc_total,
                accounted - last_accounted, accounted,
                (int) mi - last_mallinfo, (int) mi,
                xmalloc_file, xmalloc_line, xmalloc_func);

        if (sign < 0)
            fprintf(stderr, " (%d %s:%d)\n", malloc_number(p), malloc_file_name(p), malloc_line_number(p));
        else
            fprintf(stderr, " %d\n", xmalloc_count);
    }

    last_total = xmalloc_total;
    last_accounted = accounted;
    last_mallinfo = mi;
}