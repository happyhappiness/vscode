u_char *
asn_build_objid(u_char * data, int *datalength,
                u_char type, oid * objid, int objidlength)
/*    u_char *data;         IN - pointer to start of object */
/*    int    *datalength;   IN/OUT - # of valid bytes left in buf */
/*    u_char  type;         IN - ASN type of object */
/*    oid    *objid;        IN - pointer to start of input buffer */
/*    int     objidlength;  IN - number of sub-id's in objid */
{
    /*
     * ASN.1 objid ::= 0x06 asnlength subidentifier {subidentifier}*
     * subidentifier ::= {leadingbyte}* lastbyte
     * leadingbyte ::= 1 7bitvalue
     * lastbyte ::= 0 7bitvalue
     */
    u_char buf[MAX_OID_LEN];
    u_char *bp = buf;
    oid *op = objid;
    int asnlength;
    u_int subid, mask, testmask;
    int bits, testbits;

    if (objidlength < 2) {
        *bp++ = 0;
        objidlength = 0;
    } else {
        *bp++ = op[1] + (op[0] * 40);
        objidlength -= 2;
        op += 2;
    }

    while (objidlength-- > 0) {
        subid = *op++;
        if (subid < 127) {  /* off by one? */
            *bp++ = subid;
        } else {
            mask = 0x7F;    /* handle subid == 0 case */
            bits = 0;
            /* testmask *MUST* !!!! be of an unsigned type */
            for (testmask = 0x7F, testbits = 0; testmask != 0;
                    testmask <<= 7, testbits += 7) {
                if (subid & testmask) {     /* if any bits set */
                    mask = testmask;
                    bits = testbits;
                }
            }
            /* mask can't be zero here */
            for (; mask != 0x7F; mask >>= 7, bits -= 7) {
                /* fix a mask that got truncated above */
                if (mask == 0x1E00000)
                    mask = 0xFE00000;
                *bp++ = (u_char) (((subid & mask) >> bits) | ASN_BIT8);
            }
            *bp++ = (u_char) (subid & mask);
        }
    }

    asnlength = bp - buf;
    data = asn_build_header_with_truth(data, datalength, type, asnlength, 1);
    if (data == NULL)
        return (NULL);
    if (*datalength < asnlength) {
        snmp_set_api_error(SNMPERR_ASN_DECODE);
        return (NULL);
    }
    memcpy((char *) data, (char *) buf, asnlength);
    *datalength -= asnlength;
    return (data + asnlength);
}