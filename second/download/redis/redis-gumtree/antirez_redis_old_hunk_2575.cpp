        incrRefCount(ele);
        setTypeRemove(set,ele);
    }

    /* Replicate/AOF this command as an SREM operation */
    aux = createStringObject("SREM",4);
