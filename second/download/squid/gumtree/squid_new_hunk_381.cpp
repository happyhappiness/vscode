        args = args->next;
    }

    storeAppendPrintf(entry, "\n");
}

inline void
free_YesNoNone(YesNoNone *)
{
    // do nothing: no explicit cleanup is required
}

