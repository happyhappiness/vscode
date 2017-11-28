fprintf(stderr, "%*s%p %s:%d size %d allocation %d\n",
                                depth, "",
                                malloc_ptrs[B][I], malloc_file[B][I],
                                malloc_line[B][I], malloc_size[B][I],
                                malloc_count[B][I]);