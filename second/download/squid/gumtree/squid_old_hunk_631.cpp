        } else {
            perror("xcalloc");
        }
        exit(1);
    }

#if XMALLOC_DEBUG
    check_malloc(p, sz * n);
#endif
#if XMALLOC_STATISTICS
    malloc_stat(sz * n);
#endif
#if MEM_GEN_TRACE
    if (tracefp)
        fprintf(tracefp, "c:%u:%u:%p\n", (unsigned int) n, (unsigned int) sz, p);
#endif

    PROF_stop(xcalloc);
    return p;
}

void *
