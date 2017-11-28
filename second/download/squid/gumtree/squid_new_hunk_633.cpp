            perror("realloc");
        }

        exit(1);
    }

#if XMALLOC_STATISTICS
    malloc_stat(sz);
#endif

    PROF_stop(xrealloc);
    return (p);
}

void
free_const(const void *s_const)
{
    void *s = const_cast<void *>(s_const);

    PROF_start(free_const);
    PROF_start(free);
    free(s);
    PROF_stop(free);
    PROF_stop(free_const);
}

