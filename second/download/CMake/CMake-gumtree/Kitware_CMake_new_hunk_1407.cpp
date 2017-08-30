
  mem=(struct memdebug *)(Curl_crealloc)(mem, size);
  if(logfile)
    fprintf(logfile, "MEM %s:%d realloc(%p, %zd) = %p\n",
            source, line, ptr, wantedsize, mem?mem->mem:NULL);

  if(mem) {