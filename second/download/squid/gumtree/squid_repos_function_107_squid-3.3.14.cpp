main(int argc, char **argv)
{
    char c;
    extern char *optarg;
    malloc_options = "A";
    a = 0;
    while ((c = getopt(argc, argv, "f:i:M:l:m:r:N")) != -1) {
        switch (c) {
        case 'N':
            mem_pools_on = 0;
            break;
        case 'r':
            run_stats = atoi(optarg);
            break;
        case 'f':
            fn = strdup(optarg);
            fp = fopen(fn, "r");
            break;
        case 'i':
            initsiz = atoi(optarg);
            break;
        case 'l':
            mem_max_size = atoi(optarg) * 1024 * 1024;
            break;
        case 'M':
            maxsiz = atoi(optarg);
            break;
        case 'm':
            minchunk = atoi(optarg);
            break;
        default:
            fprintf(stderr,
                    "Usage: %s -f file -M maxsiz -i initsiz -m minchunk", argv[0]);
            exit(1);
        }

    }
    if (!fp) {
        fprintf(stderr,
                "%s pummels %s\n%s . o O ( You't supply a valid tracefile.)\n",
                argv[0], getenv("USER"), argv[0]);
        exit(1);
    }
#ifdef WITH_LIB
    sizeToPoolInit();
#endif
    mem_table = hash_create(ptrcmp, 229, hash4);	/* small hash table */
    init_stats();
    while (fgets(mbuf, 256, fp) != NULL) {
        if (run_stats > 0 && (++a) % run_stats == 0)
            print_stats();
        p = NULL;
        switch (mbuf[0]) {
        case 'm':		/* malloc */
            p = strtok(&mbuf[2], ":");
            if (!p)
                badformat();
            size = atoi(p);
            p = strtok(NULL, "\n");
            if (!p)
                badformat();
            mi = malloc(sizeof(memitem));
            strcpy(mi->orig_ptr, p);
            mi->size = size;
            size2id(size, mi);
            mi->my_ptr = xmemAlloc(mi);		/* (void *)xmalloc(size); */
            assert(mi->my_ptr);
            my_hash_insert(mem_table, mi->orig_ptr, mi);
            mstat.mallocs++;
            break;
        case 'c':		/* calloc */
            p = strtok(&mbuf[2], ":");
            if (!p)
                badformat();
            amt = atoi(p);
            p = strtok(NULL, ":");
            if (!p)
                badformat();
            size = atoi(p);
            p = strtok(NULL, "\n");
            if (!p)
                badformat();
            mi = malloc(sizeof(memitem));
            strcpy(mi->orig_ptr, p);
            size2id(size, mi);
            mi->size = amt * size;
            mi->my_ptr = xmemAlloc(mi);		/*(void *)xmalloc(amt*size); */
            assert(mi->my_ptr);
            my_hash_insert(mem_table, mi->orig_ptr, mi);
            mstat.callocs++;
            break;
        case 'r':
            p = strtok(&mbuf[2], ":");
            if (!p)
                badformat();
            strcpy(abuf, p);
            p = strtok(NULL, ":");
            if (!p)
                badformat();
            mem_entry = hash_lookup(mem_table, p);
            if (mem_entry == NULL) {
                fprintf(stderr, "invalid realloc (%s)!\n", p);
                break;
            }
            mi = (memitem *) (mem_entry->item);
            assert(mi->pool);
            assert(mi->my_ptr);
            xmemFree(mi);	/* xfree(mi->my_ptr); */
            size2id(atoi(p), mi);	/* we don't need it here I guess? */
            strcpy(mi->orig_ptr, abuf);
            p = strtok(NULL, "\n");
            if (!p)
                badformat();
            mi->my_ptr = xmemAlloc(mi);		/* (char *)xmalloc(atoi(p)); */
            assert(mi->my_ptr);
            mstat.reallocs++;
            break;
        case 'f':
            p = strtok(&mbuf[2], "\n");
            mem_entry = hash_lookup(mem_table, p);
            if (mem_entry == NULL) {
                if (p[0] != '0')
                    fprintf(stderr, "invalid free (%s) at line %d!\n", p, a);
                break;
            }
            mi = (memitem *) (mem_entry->item);
            assert(mi->pool);
            assert(mi->my_ptr);
            xmemFree(mi);	/* xfree(mi->my_ptr); */
            hash_unlink(mem_table, mem_entry, 1);
            free(mi);
            mstat.frees++;
            break;
        default:
            fprintf(stderr, "%s pummels %s.bad.format\n", argv[0], fn);
            exit(1);
        }

    }
    fclose(fp);
    print_stats();
}