static void
xmalloc_show_trace(void *p, int sign)
{
    int statMemoryAccounted();
    static size_t last_total = 0, last_accounted = 0, last_mallinfo = 0;
    size_t accounted = statMemoryAccounted();
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
        fprintf(stderr, "%c%8p size=%5d/%d acc=%5d/%d mallinfo=%5d/%d %s:%d %s",
                sign > 0 ? '+' : '-', p,
                (int) xmalloc_total - last_total, (int) xmalloc_total,
                (int) accounted - last_accounted, (int) accounted,
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