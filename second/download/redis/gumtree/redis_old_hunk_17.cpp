
    /* Update byte with new bit value and return original value */
    byteval &= ~(1 << bit);
    byteval |= ((on & 0x1) << bit);
    ((uint8_t*)o->ptr)[byte] = byteval;
    signalModifiedKey(c->db,c->argv[1]);
    server.dirty++;
    addReply(c, bitval ? shared.cone : shared.czero);
}

/* GETBIT key offset */
void getbitCommand(redisClient *c) {
