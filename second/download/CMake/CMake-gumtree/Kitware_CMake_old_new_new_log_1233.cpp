fprintf(logfile, "MEM %s:%d realloc(%p, %zd) = %p\n",
            source, line, ptr, wantedsize, mem?mem->mem:NULL);