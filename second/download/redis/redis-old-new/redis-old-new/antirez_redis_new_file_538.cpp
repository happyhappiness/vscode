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
static inline int decodeGeohash(double bits, double *latlong) {
    GeoHashBits hash = { .bits = (uint64_t)bits, .step = GEO_STEP_MAX };
    return geohashDecodeToLatLongWGS84(hash, latlong);
}

/* Input Argument Helper */
/* Take a pointer to the latitude arg then use the next arg for longitude.
 * On parse error REDIS_ERR is returned, otherwise REDIS_OK. */
static inline int extractLatLongOrReply(redisClient *c, robj **argv,
                                         double *latlong) {
    for (int i = 0; i < 2; i++) {
        if (getDoubleFromObjectOrReply(c, argv[i], latlong + i, NULL) !=
            REDIS_OK) {
            return REDIS_ERR;
        }
    }
    return REDIS_OK;
}

/* Input Argument Helper */
/* Decode lat/long from a zset member's score.
 * Returns REDIS_OK on successful decoding, otherwise REDIS_ERR is returned. */
static int latLongFromMember(robj *zobj, robj *member, double *latlong) {
    double score = 0;

    if (zsetScore(zobj, member, &score) == REDIS_ERR) return REDIS_ERR;
    if (!decodeGeohash(score, latlong)) return REDIS_ERR;
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

    return distance * to_meters;
}

/* The defailt addReplyDouble has too much accuracy.  We use this
 * for returning location distances. "5.2145 meters away" is nicer
 * than "5.2144992818115 meters away." We provide 4 digits after the dot
 * so that the returned value is decently accurate even when the unit is
 * the kilometer. */
static inline void addReplyDoubleDistance(redisClient *c, double d) {
    char dbuf[128];
    int dlen = snprintf(dbuf, sizeof(dbuf), "%.4f", d);
    addReplyBulkCBuffer(c, dbuf, dlen);
}

/* Helper function for geoGetPointsInRange(): given a sorted set score
 * representing a point, and another point (the center of our search) and
 * a radius, appends this entry as a geoPoint into the specified geoArray
 * only if the point is within the search area.
 *
 * returns REDIS_OK if the point is included, or REIDS_ERR if it is outside. */
int geoAppendIfWithinRadius(geoArray *ga, double lat, double lon, double radius, double score, sds member) {
    double distance, latlong[2];

    if (!decodeGeohash(score,latlong)) return REDIS_ERR; /* Can't decode. */
    /* Note that geohashGetDistanceIfInRadiusWGS84() takes arguments in
     * reverse order: longitude first, latitude later. */
    if (!geohashGetDistanceIfInRadiusWGS84(lon,lat,latlong[1], latlong[0],
                                           radius, &distance))
    {
        return REDIS_ERR;
    }

    /* Append the new element. */
    geoPoint *gp = geoArrayAppend(ga);
    gp->latitude = latlong[0];
    gp->longitude = latlong[1];
    gp->dist = distance;
    gp->member = member;
    gp->score = score;
    return REDIS_OK;
}

/* Query a Redis sorted set to extract all the elements between 'min' and
 * 'max', appending them into the array of geoPoint structures 'gparray'.
 * The command returns the number of elements added to the array.
 *
 * Elements which are farest than 'radius' from the specified 'x' and 'y'
 * coordinates are not included.
 *
 * The ability of this function to append to an existing set of points is
 * important for good performances because querying by radius is performed
 * using multiple queries to the sorted set, that we later need to sort
 * via qsort. Similarly we need to be able to reject points outside the search
 * radius area ASAP in order to allocate and process more points than needed. */
int geoGetPointsInRange(robj *zobj, double min, double max, double lat, double lon, double radius, geoArray *ga) {
    /* minex 0 = include min in range; maxex 1 = exclude max in range */
    /* That's: min <= val < max */
    zrangespec range = { .min = min, .max = max, .minex = 0, .maxex = 1 };
    size_t origincount = ga->used;
    sds member;

    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
        unsigned char *zl = zobj->ptr;
        unsigned char *eptr, *sptr;
        unsigned char *vstr = NULL;
        unsigned int vlen = 0;
        long long vlong = 0;
        double score = 0;

        if ((eptr = zzlFirstInRange(zl, &range)) == NULL) {
            /* Nothing exists starting at our min.  No results. */
            return 0;
        }

        sptr = ziplistNext(zl, eptr);
        while (eptr) {
            score = zzlGetScore(sptr);

            /* If we fell out of range, break. */
            if (!zslValueLteMax(score, &range))
                break;

            /* We know the element exists. ziplistGet should always succeed */
            ziplistGet(eptr, &vstr, &vlen, &vlong);
            member = (vstr == NULL) ? sdsfromlonglong(vlong) :
                                      sdsnewlen(vstr,vlen);
            if (geoAppendIfWithinRadius(ga,lat,lon,radius,score,member)
                == REDIS_ERR) sdsfree(member);
            zzlNext(zl, &eptr, &sptr);
        }
    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
        zset *zs = zobj->ptr;
        zskiplist *zsl = zs->zsl;
        zskiplistNode *ln;

        if ((ln = zslFirstInRange(zsl, &range)) == NULL) {
            /* Nothing exists starting at our min.  No results. */
            return 0;
        }

        while (ln) {
            robj *o = ln->obj;
            /* Abort when the node is no longer in range. */
            if (!zslValueLteMax(ln->score, &range))
                break;

            member = (o->encoding == REDIS_ENCODING_INT) ?
                        sdsfromlonglong((long)o->ptr) :
                        sdsdup(o->ptr);
            if (geoAppendIfWithinRadius(ga,lat,lon,radius,ln->score,member)
                == REDIS_ERR) sdsfree(member);
            ln = ln->level[0].forward;
        }
    }
    return ga->used - origincount;
}

/* Obtain all members between the min/max of this geohash bounding box.
 * Populate a geoArray of GeoPoints by calling geoGetPointsInRange().
 * Return the number of points added to the array. */
int membersOfGeoHashBox(robj *zobj, GeoHashBits hash, geoArray *ga, double lat, double lon, double radius) {
    GeoHashFix52Bits min, max;

    min = geohashAlign52Bits(hash);
    hash.bits++;
    max = geohashAlign52Bits(hash);

    return geoGetPointsInRange(zobj, min, max, lat, lon, radius, ga);
}

/* Search all eight neighbors + self geohash box */
int membersOfAllNeighbors(robj *zobj, GeoHashRadius n, double lat, double lon, double radius, geoArray *ga) {
    GeoHashBits neighbors[9];
    unsigned int i, count = 0;

    neighbors[0] = n.hash;
    neighbors[1] = n.neighbors.north;
    neighbors[2] = n.neighbors.south;
    neighbors[3] = n.neighbors.east;
    neighbors[4] = n.neighbors.west;
    neighbors[5] = n.neighbors.north_east;
    neighbors[6] = n.neighbors.north_west;
    neighbors[7] = n.neighbors.south_east;
    neighbors[8] = n.neighbors.south_west;

    /* For each neighbor (*and* our own hashbox), get all the matching
     * members and add them to the potential result list. */
    for (i = 0; i < sizeof(neighbors) / sizeof(*neighbors); i++) {
        if (HASHISZERO(neighbors[i]))
            continue;
        count += membersOfGeoHashBox(zobj, neighbors[i], ga, lat, lon, radius);
    }
    return count;
}

/* Sort comparators for qsort() */
static int sort_gp_asc(const void *a, const void *b) {
    const struct geoPoint *gpa = a, *gpb = b;
    /* We can't do adist - bdist because they are doubles and
     * the comparator returns an int. */
    if (gpa->dist > gpb->dist)
        return 1;
    else if (gpa->dist == gpb->dist)
        return 0;
    else
        return -1;
}

static int sort_gp_desc(const void *a, const void *b) {
    return -sort_gp_asc(a, b);
}

/* ====================================================================
 * Commands
 * ==================================================================== */
void geoAddCommand(redisClient *c) {
    /* args 0-4: [cmd, key, lat, lng, val]; optional 5-6: [radius, units]
     * - OR -
     * args 0-N: [cmd, key, lat, lng, val, lat2, lng2, val2, ...] */

    /* Prepare for the three different forms of the add command. */
    double radius_meters = 0;
    if (c->argc == 7) {
        if ((radius_meters = extractDistanceOrReply(c, c->argv + 5, NULL)) <
            0) {
            return;
        }
    } else if (c->argc == 6) {
        addReplyError(c, "must provide units when asking for radius encode");
        return;
    } else if ((c->argc - 2) % 3 != 0) {
        /* Need an odd number of arguments if we got this far... */
        addReplyError(c, "format is: geoadd [key] [lat1] [long1] [member1] "
                         "[lat2] [long2] [member2] ... ");
        return;
    }

    int elements = (c->argc - 2) / 3;
    int argc = 2+elements*2; /* ZADD key score ele ... */
    robj **argv = zcalloc(argc*sizeof(robj*));
    argv[0] = createRawStringObject("zadd",4);
    argv[1] = c->argv[1]; /* key */
    incrRefCount(argv[1]);

    /* Create the argument vector to call ZADD in order to add all
     * the score,value pairs to the requested zset, where score is actually
     * an encoded version of lat,long. */
    uint8_t step = geohashEstimateStepsByRadius(radius_meters);
    int i;
    for (i = 0; i < elements; i++) {
        double latlong[elements * 2];

        if (extractLatLongOrReply(c, (c->argv+2)+(i*3),latlong) == REDIS_ERR) {
            for (i = 0; i < argc; i++)
                if (argv[i]) decrRefCount(argv[i]);
            zfree(argv);
            return;
        }

#ifdef DEBUG
        printf("Adding with step size: %d\n", step);
#endif

        /* Turn the coordinates into the score of the element. */
        GeoHashBits hash;
        double latitude = latlong[0];
        double longitude = latlong[1];
        geohashEncodeWGS84(latitude, longitude, step, &hash);

        GeoHashFix52Bits bits = geohashAlign52Bits(hash);
        robj *score = createObject(REDIS_STRING, sdsfromlonglong(bits));
        robj *val = c->argv[2 + i * 3 + 2];
        argv[2+i*2] = score;
        argv[3+i*2] = val;
        incrRefCount(val);
    }

    /* Finally call ZADD that will do the work for us. */
    replaceClientCommandVector(c,argc,argv);
    zaddCommand(c);
}

#define SORT_NONE 0
#define SORT_ASC 1
#define SORT_DESC 2

#define RADIUS_COORDS 1
#define RADIUS_MEMBER 2

static void geoRadiusGeneric(redisClient *c, int type) {
    /* type == cords:  [cmd, key, lat, long, radius, units, [optionals]]
     * type == member: [cmd, key, member,    radius, units, [optionals]] */
    robj *key = c->argv[1];

    /* Look up the requested zset */
    robj *zobj = NULL;
    if ((zobj = lookupKeyReadOrReply(c, key, shared.emptymultibulk)) == NULL ||
        checkType(c, zobj, REDIS_ZSET)) {
        return;
    }

    /* Find lat/long to use for radius search based on inquiry type */
    int base_args;
    double latlong[2] = { 0 };
    if (type == RADIUS_COORDS) {
        base_args = 6;
        if (extractLatLongOrReply(c, c->argv + 2, latlong) == REDIS_ERR)
            return;
    } else if (type == RADIUS_MEMBER) {
        base_args = 5;
        robj *member = c->argv[2];
        if (latLongFromMember(zobj, member, latlong) == REDIS_ERR) {
            addReplyError(c, "could not decode requested zset member");
            return;
        }
    } else {
        addReplyError(c, "unknown georadius search type");
        return;
    }

    /* Extract radius and units from arguments */
    double radius_meters = 0, conversion = 1;
    if ((radius_meters = extractDistanceOrReply(c, c->argv + base_args - 2,
                                                &conversion)) < 0) {
        return;
    }

    /* Discover and populate all optional parameters. */
    int withdist = 0, withhash = 0, withcoords = 0, noproperties = 0;
    int sort = SORT_NONE;
    if (c->argc > base_args) {
        int remaining = c->argc - base_args;
        for (int i = 0; i < remaining; i++) {
            char *arg = c->argv[base_args + i]->ptr;
            if (!strncasecmp(arg, "withdist", 8))
                withdist = 1;
            else if (!strcasecmp(arg, "withhash"))
                withhash = 1;
            else if (!strncasecmp(arg, "withcoord", 9))
                withcoords = 1;
            else if (!strncasecmp(arg, "noprop", 6) ||
                     !strncasecmp(arg, "withoutprop", 11))
                noproperties = 1;
            else if (!strncasecmp(arg, "asc", 3) ||
                     !strncasecmp(arg, "sort", 4))
                sort = SORT_ASC;
            else if (!strncasecmp(arg, "desc", 4))
                sort = SORT_DESC;
            else {
                addReply(c, shared.syntaxerr);
                return;
            }
        }
    }

    /* Get all neighbor geohash boxes for our radius search */
    GeoHashRadius georadius =
        geohashGetAreasByRadiusWGS84(latlong[0], latlong[1], radius_meters);

#ifdef DEBUG
    printf("Searching with step size: %d\n", georadius.hash.step);
#endif

    /* Search the zset for all matching points */
    geoArray *ga = geoArrayCreate();
    membersOfAllNeighbors(zobj, georadius, latlong[0], latlong[1], radius_meters, ga);

    /* If no matching results, the user gets an empty reply. */
    if (ga->used == 0) {
        addReply(c, shared.emptymultibulk);
        geoArrayFree(ga);
        return;
    }

    long result_length = ga->used;
    long option_length = 0;

    /* Our options are self-contained nested multibulk replies, so we
     * only need to track how many of those nested replies we return. */
    if (withdist)
        option_length++;

    if (withcoords)
        option_length++;

    if (withhash)
        option_length++;

    /* The multibulk len we send is exactly result_length. The result is either
     * all strings of just zset members  *or* a nested multi-bulk reply
     * containing the zset member string _and_ all the additional options the
     * user enabled for this request. */
    addReplyMultiBulkLen(c, result_length);

    /* Process [optional] requested sorting */
    if (sort == SORT_ASC) {
        qsort(ga->array, result_length, sizeof(geoPoint), sort_gp_asc);
    } else if (sort == SORT_DESC) {
        qsort(ga->array, result_length, sizeof(geoPoint), sort_gp_desc);
    }

    /* Finally send results back to the caller */
    int i;
    for (i = 0; i < result_length; i++) {
        geoPoint *gp = ga->array+i;
        gp->dist /= conversion; /* Fix according to unit. */

        /* If we have options in option_length, return each sub-result
         * as a nested multi-bulk.  Add 1 to account for result value itself. */
        if (option_length)
            addReplyMultiBulkLen(c, option_length + 1);

        addReplyBulkSds(c,gp->member);
        gp->member = NULL;

        if (withdist)
            addReplyDoubleDistance(c, gp->dist);

        if (withhash)
            addReplyLongLong(c, gp->score);

        if (withcoords) {
            addReplyMultiBulkLen(c, 2);
            addReplyDouble(c, gp->latitude);
            addReplyDouble(c, gp->longitude);
        }
    }
    geoArrayFree(ga);
}

void geoRadiusCommand(redisClient *c) {
    /* args 0-5: ["georadius", key, lat, long, radius, units];
     * optionals: [withdist, withcoords, asc|desc] */
    geoRadiusGeneric(c, RADIUS_COORDS);
}

void geoRadiusByMemberCommand(redisClient *c) {
    /* args 0-4: ["georadius", key, compare-against-member, radius, units];
     * optionals: [withdist, withcoords, asc|desc] */
    geoRadiusGeneric(c, RADIUS_MEMBER);
}

void geoDecodeCommand(redisClient *c) {
    GeoHashBits geohash;
    if (getLongLongFromObjectOrReply(c, c->argv[1], (long long *)&geohash.bits,
                                     NULL) != REDIS_OK)
        return;

    GeoHashArea area;
    geohash.step = GEO_STEP_MAX;
    geohashDecodeWGS84(geohash, &area);

    double lat = (area.latitude.min + area.latitude.max) / 2;
    double lon = (area.longitude.min + area.longitude.max) / 2;

    /* Returning three nested replies */
    addReplyMultiBulkLen(c, 3);

    /* First, the minimum corner */
    addReplyMultiBulkLen(c, 2);
    addReplyDouble(c, area.latitude.min);
    addReplyDouble(c, area.longitude.min);

    /* Next, the maximum corner */
    addReplyMultiBulkLen(c, 2);
    addReplyDouble(c, area.latitude.max);
    addReplyDouble(c, area.longitude.max);

    /* Last, the averaged center of this bounding box */
    addReplyMultiBulkLen(c, 2);
    addReplyDouble(c, lat);
    addReplyDouble(c, lon);
}

void geoEncodeCommand(redisClient *c) {
    /* args 0-2: ["geoencode", lat, long];
     * optionals: [radius, units] */

    double radius_meters = 0;
    if (c->argc >= 5) {
        if ((radius_meters = extractDistanceOrReply(c, c->argv + 3, NULL)) < 0)
            return;
    } else if (c->argc == 4) {
        addReplyError(c, "must provide units when asking for radius encode");
        return;
    }

    double latlong[2];
    if (extractLatLongOrReply(c, c->argv + 1, latlong) == REDIS_ERR) return;

    /* Encode lat/long into our geohash */
    GeoHashBits geohash;
    uint8_t step = geohashEstimateStepsByRadius(radius_meters);
    geohashEncodeWGS84(latlong[0], latlong[1], step, &geohash);

    /* Align the hash to a valid 52-bit integer based on step size */
    GeoHashFix52Bits bits = geohashAlign52Bits(geohash);

/* Decode the hash so we can return its bounding box */
#ifdef DEBUG
    printf("Decoding with step size: %d\n", geohash.step);
#endif
    GeoHashArea area;
    geohashDecodeWGS84(geohash, &area);

    double lat = (area.latitude.min + area.latitude.max) / 2;
    double lon = (area.longitude.min + area.longitude.max) / 2;

    /* Return four nested multibulk replies. */
    addReplyMultiBulkLen(c, 4);

    /* Return the binary geohash we calculated as 52-bit integer */
    addReplyLongLong(c, bits);

    /* Return the minimum corner */
    addReplyMultiBulkLen(c, 2);
    addReplyDouble(c, area.latitude.min);
    addReplyDouble(c, area.longitude.min);

    /* Return the maximum corner */
    addReplyMultiBulkLen(c, 2);
    addReplyDouble(c, area.latitude.max);
    addReplyDouble(c, area.longitude.max);

    /* Return the averaged center */
    addReplyMultiBulkLen(c, 2);
    addReplyDouble(c, lat);
    addReplyDouble(c, lon);
}
