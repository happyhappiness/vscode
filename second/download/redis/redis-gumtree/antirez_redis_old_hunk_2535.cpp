        incrRefCount(ele);
        setTypeRemove(set,ele);
    }
    notifyKeyspaceEvent("spop",c->argv[1],c->db->id);

    /* Replicate/AOF this command as an SREM operation */
    aux = createStringObject("SREM",4);
