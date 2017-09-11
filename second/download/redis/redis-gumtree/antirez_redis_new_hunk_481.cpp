#define BITOP_XOR   2
#define BITOP_NOT   3

#define BITFIELDOP_GET 0
#define BITFIELDOP_SET 1
#define BITFIELDOP_INCRBY 2

/* This helper function used by GETBIT / SETBIT parses the bit offset argument
 * making sure an error is returned if it is negative or if it overflows
 * Redis 512 MB limit for the string value. */
int getBitOffsetFromArgument(client *c, robj *o, size_t *offset) {
    long long loffset;
    char *err = "bit offset is not an integer or out of range";

    if (getLongLongFromObjectOrReply(c,o,&loffset,err) != C_OK)
        return C_ERR;

    /* Limit offset to 512MB in bytes */
    if ((loffset < 0) || ((unsigned long long)loffset >> 3) >= (512*1024*1024))
    {
        addReplyError(c,err);
        return C_ERR;
    }

    *offset = (size_t)loffset;
    return C_OK;
}

/* This helper function for BITFIELD parses a bitfield type in the form
 * <sign><bits> where sign is 'u' or 'i' for unsigned and signed, and
 * the bits is a value between 1 and 64. However 64 bits unsigned integers
 * are reported as an error because of current limitations of Redis protocol
 * to return unsigned integer values greater than INT64_MAX.
 *
 * On error C_ERR is returned and an error is sent to the client. */
int getBitfieldTypeFromArgument(client *c, robj *o, int *sign, int *bits) {
    char *p = o->ptr;
    char *err = "Invalid bitfield type. Use something like i16 u8. Note that u64 is not supported but i64 is.";
    long long llbits;

    if (p[0] == 'i') {
        *sign = 1;
    } else if (p[0] == 'u') {
        *sign = 0;
    } else {
        addReplyError(c,err);
        return C_ERR;
    }

    if ((string2ll(p+1,strlen(p+1),&llbits)) == 0 ||
        llbits < 1 ||
        (*sign == 1 && llbits > 63) ||
        (*sign == 0 && llbits > 64))
    {
        addReplyError(c,err);
        return C_ERR;
    }
    *bits = llbits;
    return C_OK;
}

/* This is an helper function for commands implementations that need to write
 * bits to a string object. The command creates or pad with zeroes the string
 * so that the 'maxbit' bit can be addressed. The object is finally
 * returned. Otherwise if the key holds a wrong type NULL is returned and
 * an error is sent to the client. */
robj *lookupStringForBitCommand(client *c, size_t maxbit) {
    size_t byte = maxbit >> 3;
    robj *o = lookupKeyWrite(c->db,c->argv[1]);

    if (o == NULL) {
        o = createObject(OBJ_STRING,sdsnewlen(NULL, byte+1));
        dbAdd(c->db,c->argv[1],o);
    } else {
        if (checkType(c,o,OBJ_STRING)) return NULL;
        o = dbUnshareStringValue(c->db,c->argv[1],o);
        o->ptr = sdsgrowzero(o->ptr,byte+1);
    }
    return o;
}

/* SETBIT key offset bitvalue */
void setbitCommand(client *c) {
    robj *o;
    char *err = "bit is not an integer or out of range";
    size_t bitoffset;
    ssize_t byte, bit;
    int byteval, bitval;
    long on;

