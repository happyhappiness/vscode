        } else {
            perror("xcalloc");
        }
        exit(1);
    }

#if XMALLOC_STATISTICS
    malloc_stat(sz * n);
#endif

    PROF_stop(xcalloc);
    return p;
}

void *
