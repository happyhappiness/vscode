/*
 * Copyright (c) 2014, Matt Stancliff <matt@genges.com>.
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

#include "geo.h"
#include "geohash_helper.h"

/* Things exported from t_zset.c only for geo.c, since it is the only other
 * part of Redis that requires close zset introspection. */
unsigned char *zzlFirstInRange(unsigned char *zl, zrangespec *range);
int zslValueLteMax(double value, zrangespec *spec);

/* ====================================================================
 * This file implements the following commands:
 *
 *   - geoadd - add coordinates for value to geoset
 *   - georadius - search radius by coordinates in geoset
 *   - georadiusbymember - search radius based on geoset member position
 *   - geoencode - encode coordinates to a geohash integer
 *   - geodecode - decode geohash integer to representative coordinates
 * ==================================================================== */

/* ====================================================================
 * geoArray implementation
 * ==================================================================== */

/* Create a new array of geoPoints. */
geoArray *geoArrayCreate(void) {
    geoArray *ga = zmalloc(sizeof(*ga));
    /* It gets allocated on first geoArrayAppend() call. */
    ga->array = NULL;
    ga->buckets = 0;
    ga->used = 0;
    return ga;
}

/* Add a new entry and return its pointer so that the caller can populate
 * it with data. */
geoPoint *geoArrayAppend(geoArray *ga) {
    if (ga->used == ga->buckets) {
        ga->buckets = (ga->buckets == 0) ? 8 : ga->buckets*2;
        ga->array = zrealloc(ga->array,sizeof(geoPoint)*ga->buckets);
    }
    geoPoint *gp = ga->array+ga->used;
    ga->used++;
    return gp;
}

/* Destroy a geoArray created with geoArrayCreate(). */
void geoArrayFree(geoArray *ga) {
    size_t i;
    for (i = 0; i < ga->used; i++) sdsfree(ga->array[i].member);
    zfree(ga->array);
    zfree(ga);
}

/* ====================================================================
 * Helpers
 * ==================================================================== */
static inline int decodeGeohash(double bits, double *xy) {
    GeoHashBits hash = { .bits = (uint64_t)bits, .step = GEO_STEP_MAX };
    return geohashDecodeToLongLatWGS84(hash, xy);
}

/* Input Argument Helper */
/* Take a pointer to the latitude arg then use the next arg for longitude.
 * On parse error REDIS_ERR is returned, otherwise REDIS_OK. */
static inline int extractLongLatOrReply(redisClient *c, robj **argv,
                                        double *xy) {
    for (int i = 0; i < 2; i++) {
        if (getDoubleFromObjectOrReply(c, argv[i], xy + i, NULL) !=
            REDIS_OK) {
            return REDIS_ERR;
        }
    }
    return REDIS_OK;
}

/* Input Argument Helper */
/* Decode lat/long from a zset member's score.
 * Returns REDIS_OK on successful decoding, otherwise REDIS_ERR is returned. */
static int longLatFromMember(robj *zobj, robj *member, double *xy) {
    double score = 0;

    if (zsetScore(zobj, member, &score) == REDIS_ERR) return REDIS_ERR;
    if (!decodeGeohash(score, xy)) return REDIS_ERR;
    return REDIS_OK;
}

/* Input Argument Helper.
 * Extract the dinstance from the specified two arguments starting at 'argv'
 * that shouldbe in the form: <number> <unit> and return the dinstance in the
 * specified unit on success. *conversino is populated with the coefficient
 * to use in order to convert meters to the unit.
 *
 * On error a value less than zero is returned. */
static double extractDistanceOrReply(redisClient *c, robj **argv,
                                     double *conversion) {
    double distance;
    if (getDoubleFromObjectOrReply(c, argv[0], &distance,
                                   "need numeric radius") != REDIS_OK) {
        return -1;
    }

    double to_meters;
    sds units = argv[1]->ptr;
    if (!strcmp(units, "m") || !strncmp(units, "meter", 5)) {
        to_meters = 1;
    } else if (!strcmp(units, "ft") || !strncmp(units, "feet", 4)) {
        to_meters = 0.3048;
    } else if (!strcmp(units, "mi") || !strncmp(units, "mile", 4)) {
        to_meters = 1609.34;
    } else if (!strcmp(units, "km") || !strncmp(units, "kilometer", 9)) {
        to_meters = 1000;
    } else {
        addReplyError(c, "unsupported unit provided. please use meters (m), "
                         "kilometers (km), miles (mi), or feet (ft)");
        return -1;
    }

    if (conversion)
        *conversion = to_meters;

