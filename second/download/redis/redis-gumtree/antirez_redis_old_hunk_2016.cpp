        o = dbUnshareStringValue(c->db,c->argv[1],o);
    }

    /* Write the resulting HLL to the destination HLL registers and
     * invalidate the cached value. */
    registers = o->ptr;
    for (j = 0; j < REDIS_HLL_REGISTERS; j++) {
        HLL_SET_REGISTER(registers,j,max[j]);
    }
    registers[REDIS_HLL_SIZE-9] |= (1<<7);

    signalModifiedKey(c->db,c->argv[1]);
    /* We generate an HLLADD event for HLLMERGE for semantical simplicity
     * since in theory this is a mass-add of elements. */
    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
    server.dirty++;
