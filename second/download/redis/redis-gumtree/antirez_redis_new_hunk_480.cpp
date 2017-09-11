    return 0; /* Just to avoid warnings. */
}

/* The following set.*Bitfield and get.*Bitfield functions implement setting
 * and getting arbitrary size (up to 64 bits) signed and unsigned integers
 * at arbitrary positions into a bitmap.
 *
 * The representation considers the bitmap as having the bit number 0 to be
 * the most significant bit of the first byte, and so forth, so for example
 * setting a 5 bits unsigned integer to value 23 at offset 7 into a bitmap
 * previously set to all zeroes, will produce the following representation:
 *
 * +--------+--------+
 * |00000001|01110000|
 * +--------+--------+
 *
 * When offsets and integer sizes are aligned to bytes boundaries, this is the
 * same as big endian, however when such alignment does not exist, its important
 * to also understand how the bits inside a byte are ordered.
 *
 * Note that this format follows the same convention as SETBIT and related
 * commands.
 */

void setUnsignedBitfield(unsigned char *p, uint64_t offset, uint64_t bits, uint64_t value) {
    uint64_t byte, bit, byteval, bitval, j;

    for (j = 0; j < bits; j++) {
        bitval = (value & (1<<(bits-1-j))) != 0;
        byte = offset >> 3;
        bit = 7 - (offset & 0x7);
        byteval = p[byte];
        byteval &= ~(1 << bit);
        byteval |= bitval << bit;
        p[byte] = byteval & 0xff;
        offset++;
    }
}

void setSignedBitfield(unsigned char *p, uint64_t offset, uint64_t bits, int64_t value) {
    uint64_t uv;

    if (value >= 0)
        uv = value;
    else
        uv = UINT64_MAX + value + 1;
    setUnsignedBitfield(p,offset,bits,uv);
}

uint64_t getUnsignedBitfield(unsigned char *p, uint64_t offset, uint64_t bits) {
    uint64_t byte, bit, byteval, bitval, j, value = 0;

    for (j = 0; j < bits; j++) {
        byte = offset >> 3;
        bit = 7 - (offset & 0x7);
        byteval = p[byte];
        bitval = (byteval >> bit) & 1;
        value = (value<<1) | bitval;
        offset++;
    }
    return value;
}

int64_t getSignedBitfield(unsigned char *p, uint64_t offset, uint64_t bits) {
    int64_t value = getUnsignedBitfield(p,offset,bits);
    /* If the top significant bit is 1, propagate it to all the
     * higher bits for two complement representation of signed
     * integers. */
    if (value & (1 << (bits-1)))
        value |= ((uint64_t)-1) << bits;
    return value;
}

/* The following two functions detect overflow of a value in the context
 * of storing it as an unsigned or signed integer with the specified
 * number of bits. The functions both take the value and a possible increment.
 * If no overflow could happen and the value+increment fit inside the limits,
 * then zero is returned, otherwise in case of overflow, 1 is returned,
 * otherwise in case of underflow, -1 is returned.
 *
 * When non-zero is returned (oferflow or underflow), if not NULL, *limit is
 * set to the value the operation should result when an overflow happens,
 * depending on the specified overflow semantics:
 *
 * For BFOVERFLOW_SAT if 1 is returned, *limit it is set maximum value that
 * you can store in that integer. when -1 is returned, *limit is set to the
 * minimum value that an integer of that size can represent.
 *
 * For BFOVERFLOW_WRAP *limit is set by performing the operation in order to
 * "wrap" around towards zero for unsigned integers, or towards the most
 * negative number that is possible to represent for signed integers. */

#define BFOVERFLOW_WRAP 0
#define BFOVERFLOW_SAT 1
#define BFOVERFLOW_FAIL 2 /* Used by the BITFIELD command implementation. */

int checkUnsignedBitfieldOverflow(uint64_t value, int64_t incr, uint64_t bits, int owtype, uint64_t *limit) {
    uint64_t max = (bits == 64) ? UINT64_MAX : ((1<<bits)-1);
    int64_t maxincr = max-value;
    int64_t minincr = -value;

    if (value > max || (incr > 0 && incr > maxincr)) {
        if (limit) {
            if (owtype == BFOVERFLOW_WRAP) {
                goto handle_wrap;
            } else if (owtype == BFOVERFLOW_SAT) {
                *limit = max;
            }
        }
        return 1;
    } else if (incr < 0 && incr < minincr) {
        if (limit) {
            if (owtype == BFOVERFLOW_WRAP) {
                goto handle_wrap;
            } else if (owtype == BFOVERFLOW_SAT) {
                *limit = 0;
            }
        }
        return -1;
    }
    return 0;

handle_wrap:
    {
        uint64_t mask = ((int64_t)-1) << bits;
        uint64_t res = value+incr;

        res &= ~mask;
        *limit = res;
    }
    return 1;
}

int checkSignedBitfieldOverflow(int64_t value, int64_t incr, uint64_t bits, int owtype, int64_t *limit) {
    int64_t max = (bits == 64) ? INT64_MAX : ((1<<(bits-1))-1);
    int64_t min = (-max)-1;

    /* Note that maxincr and minincr could overflow, but we use the values
     * only after checking 'value' range, so when we use it no overflow
     * happens. */
    int64_t maxincr = max-value;
    int64_t minincr = min-value;

    if (value > max || (value >= 0 && incr > 0 && incr > maxincr)) {
        if (limit) {
            if (owtype == BFOVERFLOW_WRAP) {
                goto handle_wrap;
            } else if (owtype == BFOVERFLOW_SAT) {
                *limit = max;
            }
        }
        return 1;
    } else if (value < min || (value < 0 && incr < 0 && incr < minincr)) {
        if (limit) {
            if (owtype == BFOVERFLOW_WRAP) {
                goto handle_wrap;
            } else if (owtype == BFOVERFLOW_SAT) {
                *limit = min;
            }
        }
        return -1;
    }
    return 0;

handle_wrap:
    {
        uint64_t mask = ((int64_t)-1) << bits;
        uint64_t msb = (uint64_t)1 << (bits-1);
        uint64_t a = value, b = incr, c;
        c = a+b; /* Perform addition as unsigned so that's defined. */

        /* If the sign bit is set, propagate to all the higher order
         * bits, to cap the negative value. If it's clear, mask to
         * the positive integer limit. */
        if (c & msb) {
            c |= mask;
        } else {
            c &= ~mask;
        }
        *limit = c;
    }
    return 1;
}

/* Debugging function. Just show bits in the specified bitmap. Not used
 * but here for not having to rewrite it when debugging is needed. */
void printBits(unsigned char *p, unsigned long count) {
    unsigned long j, i, byte;

    for (j = 0; j < count; j++) {
        byte = p[j];
        for (i = 0x80; i > 0; i /= 2)
            printf("%c", (byte & i) ? '1' : '0');
        printf("|");
    }
    printf("\n");
}

/* -----------------------------------------------------------------------------
 * Bits related string commands: GETBIT, SETBIT, BITCOUNT, BITOP.
 * -------------------------------------------------------------------------- */
