fprintf(logfile, "MEM %s:%d realloc(0x%x, %zd) = %p\n",
            source, line, ptr, wantedsize, mem?mem->mem:NULL);