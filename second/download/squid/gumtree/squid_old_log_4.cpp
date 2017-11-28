fprintf(stderr, "%c%8p size=%5d/%d acc=%5.0f/%.0f mallinfo=%5d/%d %s:%d %s",
                sign > 0 ? '+' : '-', p,
                (int) xmalloc_total - last_total, (int) xmalloc_total,
                accounted - last_accounted, accounted,
                (int) mi - last_mallinfo, (int) mi,
                xmalloc_file, xmalloc_line, xmalloc_func);