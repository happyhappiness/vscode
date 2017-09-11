    byteval |= ((on & 0x1) << bit);
    ((uint8_t*)o->ptr)[byte] = byteval;
    signalModifiedKey(c->db,c->argv[1]);
    server.dirty++;
    addReply(c, bitval ? shared.cone : shared.czero);
}
