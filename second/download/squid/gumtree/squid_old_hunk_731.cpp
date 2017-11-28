        *P = p->next;
#if USE_CACHE_DIGESTS

        cbdataReferenceDone(p->digest);
#endif

        cbdataFree(p);
    }

    Config.npeers = 0;
}

