/* hyperloglog.c - Redis HyperLogLog probabilistic cardinality approximation.
 * This file implements the algorithm and the exported Redis commands.
 *
 * Copyright (c) 2014, Salvatore Sanfilippo <antirez at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdint.h>
#include <math.h>
#include "redis.h"

/* The Redis HyperLogLog implementation is based on the following ideas:
 *
 * * The use of a 64 bit hash function as proposed in [1], in order to don't
 *   limited to cardinalities up to 10^9, at the cost of just 1 additional
 *   bit per register.
 * * The use of 16384 6-bit registers for a great level of accuracy, using
 *   a total of 12k per key.
 * * The use of the Redis string data type. No new type is introduced.
 * * No attempt is made to compress the data structure as in [1]. Also the
 *   algorithm used is the original HyperLogLog Algorithm as in [2], with
 *   the only difference that a 64 bit hash function is used, so no correction
 *   is performed for values near 2^32 as in [1].
 *
 * [1] Heule, Nunkesser, Hall: HyperLogLog in Practice: Algorithmic
 *     Engineering of a State of The Art Cardinality Estimation Algorithm.
 *
 * [2] P. Flajolet, Éric Fusy, O. Gandouet, and F. Meunier. Hyperloglog: The
 *     analysis of a near-optimal cardinality estimation algorithm.
 */

#define REDIS_HLL_P 14 /* The greater is P, the smaller the error. */
#define REDIS_HLL_REGISTERS (1<<REDIS_HLL_P) /* With P=14, 16384 registers. */
#define REDIS_HLL_P_MASK (REDIS_HLL_REGISTERS-1) /* Mask to index register. */
#define REDIS_HLL_BITS 6 /* Enough to count up to 63 leading zeroes. */
#define REDIS_HLL_REGISTER_MAX ((1<<REDIS_HLL_BITS)-1)
#define REDIS_HLL_SIZE ((REDIS_HLL_REGISTERS*REDIS_HLL_BITS+7)/8)

/* =========================== Low level bit macros ========================= */

/* We need to get and set 6 bit counters in an array of 8 bit bytes.
 * We use macros to make sure the code is inlined since speed is critical
 * especially in order to compute the approximated cardinality in
 * HLLCOUNT where we need to access all the registers at once.
 * For the same reason we also want to avoid conditionals in this code path.
 *
 * +--------+--------+--------+------//
 * |00000011|11112222|22333333|444444
 * +--------+--------+--------+------//
 *
 * Assuming we want to access counter at zero based index 'pos' = 2.
 * (In the example it is "222222")
 *
 * The first byte "b" containing our data is:
 *   b = 6 * pos / 8 -> 1
 *
 *   +--------+
 *   |11112222|  <- Our byte at "b"
 *   +--------+
 *
 * The amount of left shifting "ls" in the first byte is:
 *   ls = 6 * pos & 7 -> 4
 *
 *   +--------+
 *   |2222    |  <- Left shift 4 pos.
 *   +--------+
 *
 * To add the bits in the next byte b+1, we need to right shift them right of
 * "rs" bits positions before xoring it to our current value in the first byte
 * (after the left shift):
 *   rs = 8 - ls -> 4
 *
 *   +--------+
 *   |    2233|  <- Byte "b+1" right shifted 4 pos.
 *   +--------+
 *
 * Now we can just bitwise-OR the two bytes and mask for 2^6-1 in order to
 * clear bits 6 and 7 if they are set, that are not part of our 6 bit unsigned
 * integer.
 *
 * -------------------------------------------------------------------------
 *
 * Setting the register is a bit more complex, let's assume that 'val'
 * is the value we want to set, already in the right range.
 *
 * We need two steps, in one we need to clear the bits, and in the other
 * we need to bitwise-OR the new bits.
 *
 * This time let's try with 'pos' = 1, so our first byte at 'b' is 0,
 *
 * "ls" is 6, and you may notice it is actually the position of the first
 * bit inside the byte. "rs" is 8-ls = 2
 *
 *   +--------+
 *   |00000011|  <- Our initial byte at "b"
 *   +--------+
 *
 * To create a AND-mask to clear the bits about this position, we just
 * initialize the mask with 2^6-1, right shift it of "ls" bits, and invert
 * it.
 *
 *   +--------+
 *   |11111100|  <- "mask" starts at 2^6-1
 *   |00000011|  <- "mask" after right shift of "ls" bits.
 *   |11111100|  <- "mask" after invert.
 *   +--------+
 *
 * Now we can bitwise-AND the byte at "b" with the mask, and bitwise-OR
 * it with "val" right-shifted of "ls" bits to set the new bits.
 *
 * Now let's focus on the next byte b+1:
 *
 *   +--------+
 *   |11112222| <- byte at b+1
 *   +--------+
 *
 * To build the AND mask we start again with the 2^6-1 value, left shift
 * it by "rs" bits, and invert it.
 *
 *   +--------+
 *   |11111100|  <- "mask" set at 2&6-1
 *   |11110000|  <- "mask" after the left shift of "rs" bits.
 *   |00001111|  <- "mask" after bitwise not.
 *   +--------+
 *
 * Now we can mask it with b+1 to clear the old bits, and bitwise-OR
 * with "val" left-shifted by "rs" bits to set the new value.
 */

/* Note: if we access the last counter, we will also access the b+1 byte
 * that is out of the array, but sds strings always have an implicit null
 * term, so the byte exists, and we can skip the conditional (or the need
 * to allocate 1 byte more explicitly). */

/* Store the value of the register at position 'regnum' into variable 'target'.
 * 'p' is an array of unsigned bytes. */
#define HLL_GET_REGISTER(target,p,regnum) do { \
    uint8_t *_p = (uint8_t*) p; \
    int _byte = regnum*REDIS_HLL_BITS/8; \
    int _leftshift = regnum*REDIS_HLL_BITS&7; \
    int _rightshift = 8 - _leftshift; \
    target = ((_p[_byte] << _leftshift) | \
             (_p[_byte+1] >> _rightshift)) & \
             REDIS_HLL_REGISTER_MAX; \
} while(0)

/* Set the value of the register at position 'regnum' to 'val'.
 * 'p' is an array of unsigned bytes. */
#define HLL_SET_REGISTER(p,regnum,val) do { \
    uint8_t *_p = (uint8_t*) p; \
    int _byte = regnum*REDIS_HLL_BITS/8; \
    int _leftshift = regnum*REDIS_HLL_BITS&7; \
    int _rightshift = 8 - _leftshift; \
    _p[_byte] &= ~(REDIS_HLL_REGISTER_MAX >> _leftshift); \
    _p[_byte] |= val >> _leftshift; \
    _p[_byte+1] &= ~(REDIS_HLL_REGISTER_MAX << _rightshift); \
    _p[_byte+1] |= val << _rightshift; \
} while(0)

/* ========================= HyperLogLog algorithm  ========================= */

/* Our hahs function is MurmurHash2, 64 bit version. */
uint64_t MurmurHash64A (const void * key, int len, unsigned int seed) {
    const uint64_t m = 0xc6a4a7935bd1e995;
    const int r = 47;
    uint64_t h = seed ^ (len * m);
    const uint64_t *data = (const uint64_t *)key;
    const uint64_t *end = data + (len/8);

    while(data != end) {
        uint64_t k = *data++;
        k *= m;
        k ^= k >> r;
        k *= m;
        h ^= k;
        h *= m;
    }

    const unsigned char *data2 = (const unsigned char*)data;

    switch(len & 7) {
    case 7: h ^= (uint64_t)data2[6] << 48;
    case 6: h ^= (uint64_t)data2[5] << 40;
    case 5: h ^= (uint64_t)data2[4] << 32;
    case 4: h ^= (uint64_t)data2[3] << 24;
    case 3: h ^= (uint64_t)data2[2] << 16;
    case 2: h ^= (uint64_t)data2[1] << 8;
    case 1: h ^= (uint64_t)data2[0];
            h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;
    return h;
}

/* "Add" the element in the hyperloglog data structure.
 * Actually nothing is added, but the max 0 pattern counter of the subset
 * the element belongs to is incremented if needed.
 *
 * 'registers' is expected to have room for REDIS_HLL_REGISTERS plus an
 * additional byte on the right. This requirement is met by sds strings
 * automatically since they are implicitly null terminated.
 *
 * The function always succeed, however if as a result of the operation
 * the approximated cardinality changed, 1 is returned. Otherwise 0
 * is returned. */
int hllAdd(uint8_t *registers, unsigned char *ele, size_t elesize) {
    uint64_t hash, bit, index;
    uint8_t oldcount, count;

    /* Count the number of zeroes starting from bit REDIS_HLL_REGISTERS
     * (that is a power of two corresponding to the first bit we don't use
     * as index). The max run can be 64-P bits.
     *
     * This may sound like inefficient, but actually in the average case
     * there are high probabilities to find a 1 after a few iterations. */
    hash = MurmurHash64A(ele,elesize,0);
    bit = REDIS_HLL_REGISTERS;
    count = 0;
    while((hash & bit) == 0) {
        count++;
        /* Test the next bit. Note that if we run out of bits in the 64
         * bit integer, bit will be set to 0, and the while test will fail,
         * so we can save the explicit check and yet the algorithm will
         * terminate. */
        bit <<= 1;
    }

    /* Update the register if this element produced a longer run of zeroes. */
    index = hash & REDIS_HLL_P_MASK; /* Index a register inside registers. */
    HLL_GET_REGISTER(oldcount,registers,index);
    if (count > oldcount) {
        HLL_SET_REGISTER(registers,index,count);
        return 1;
    } else {
        return 0;
    }
}

/* Return the approximated cardinality of the set based on the armonic
 * mean of the registers values. */
uint64_t hllCount(uint8_t *registers) {
    double m = REDIS_HLL_REGISTERS;
    double alpha = 0.7213/(1+1.079/m);
    double E = 0;
    int ez = 0; /* Number of registers equal to 0. */
    int j;

    for (j = 0; j < REDIS_HLL_REGISTERS; j++) {
        uint8_t reg;

        /* Compute SUM(2^-register[0..i]). */
        HLL_GET_REGISTER(reg,registers,j);
        if (reg == 0) {
            ez++;
            E += 1; /* 2^(-reg[j]) is 1 when m is 0. */
        } else {
            E += 1.0/(2ULL << reg); /* 2^(-reg[j]) is the same as 1/2^reg[j]. */
        }
    }
    /* Muliply the inverse of E for alpha_m * m^2 to have the raw estimate. */
    E = (1/E)*alpha*m*m;

    /* Apply corrections for small cardinalities. */
    if (E < m*2.5 && ez != 0) {
        E = m*log(m/ez); /* LINEARCOUNTING() */
    }
    /* We don't apply the correction for E > 1/30 of 2^32 since we use
     * a 64 bit function and 6 bit counters. To apply the correction for
     * 1/30 of 2^64 is not needed since it would require a huge set
     * to approach such a value. */
    return (uint64_t) E;
}

/* ========================== HyperLogLog commands ========================== */

/* HLLADD var ele ele ele ... ele => :0 or :1 */
void hllAddCommand(redisClient *c) {
    robj *o = lookupKeyWrite(c->db,c->argv[1]);
    uint8_t *registers;
    int updated = 0, j;

    if (o == NULL) {
        /* Create the key with a string value of the exact length to
         * hold our HLL data structure. sdsnewlen() when NULL is passed
         * is guaranteed to return bytes initialized to zero. */
        o = createObject(REDIS_STRING,sdsnewlen(NULL,REDIS_HLL_SIZE));
        dbAdd(c->db,c->argv[1],o);
    } else {
        /* Key exists, check type */
        if (checkType(c,o,REDIS_STRING))
            return;

        /* If this is a string representing an HLL, the size should match
         * exactly. */
        if (stringObjectLen(o) != REDIS_HLL_SIZE) {
            addReplyErrorFormat(c,
                "HLLADD target key must contain a %d bytes string.",
                REDIS_HLL_SIZE);
            return;
        }

        /* If the object is shared or encoded, we have to make a copy. */
        if (o->refcount != 1 || o->encoding != REDIS_ENCODING_RAW) {
            robj *decoded = getDecodedObject(o);
            o = createRawStringObject(decoded->ptr, sdslen(decoded->ptr));
            decrRefCount(decoded);
            dbOverwrite(c->db,c->argv[1],o);
        }
    }
    /* Perform the low level ADD operation for every element. */
    registers = o->ptr;
    for (j = 2; j < c->argc; j++) {
        if (hllAdd(registers, (unsigned char*)c->argv[j]->ptr,
                sdslen(c->argv[j]->ptr)))
        {
            updated++;
        }
    }
    if (updated) {
        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"hlladd",c->argv[1],c->db->id);
        server.dirty++;
    }
    addReply(c, updated ? shared.cone : shared.czero);
}

/* HLLCOUNT var -> approximated cardinality of set. */
void hllCountCommand(redisClient *c) {
    robj *o = lookupKeyRead(c->db,c->argv[1]);
    uint8_t *registers;

    if (o == NULL) {
        /* No key? Cardinality is zero since no element was added, otherwise
         * we would have a key as HHLADD creates it as a side effect. */
        addReply(c,shared.czero);
    } else {
        /* Key exists, check type */
        if (checkType(c,o,REDIS_STRING))
            return;

        /* If this is a string representing an HLL, the size should match
         * exactly. */
        if (stringObjectLen(o) != REDIS_HLL_SIZE) {
            addReplyErrorFormat(c,
                "HLLCOUNT target key must contain a %d bytes string.",
                REDIS_HLL_SIZE);
            return;
        }
        registers = o->ptr;
        addReplyLongLong(c,hllCount(registers));
    }
}


/* This command performs a self-test of the HLL registers implementation.
 * Something that is not easy to test from within the outside.
 *
 * The test is conceived to test that the different counters of our data
 * structure are accessible and that setting their values both result in
 * the correct value to be retained and not affect adjacent values. */

#define REDIS_HLL_TEST_CYCLES 1000
void hllSelftestCommand(redisClient *c) {
    int j, i;
    sds bitcounters = sdsnewlen(NULL,REDIS_HLL_SIZE);
    uint8_t bytecounters[REDIS_HLL_REGISTERS];

    for (j = 0; j < REDIS_HLL_TEST_CYCLES; j++) {
        /* Set the HLL counters and an array of unsigned byes of the
         * same size to the same set of random values. */
        for (i = 0; i < REDIS_HLL_REGISTERS; i++) {
            unsigned int r = rand() & REDIS_HLL_REGISTER_MAX;

            bytecounters[i] = r;
            HLL_SET_REGISTER(bitcounters,i,r);
        }
        /* Check that we are able to retrieve the same values. */
        for (i = 0; i < REDIS_HLL_REGISTERS; i++) {
            unsigned int val;

            HLL_GET_REGISTER(val,bitcounters,i);
            if (val != bytecounters[i]) {
                addReplyErrorFormat(c,
                    "TESTFAILED Register %d should be %d but is %d",
                    i, (int) bytecounters[i], (int) val);
                goto cleanup;
            }
        }
    }

    /* Success! */
    addReply(c,shared.ok);

cleanup:
    sdsfree(bitcounters);
}
