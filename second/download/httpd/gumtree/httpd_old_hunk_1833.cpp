 *  ssl_scache_shmcb.c
 *  Session Cache via Shared Memory (Cyclic Buffer Variant)
 */

#include "ssl_private.h"

/*
 * This shared memory based SSL session cache implementation was
 * originally written by Geoff Thorpe <geoff geoffthorpe.net> for C2Net
 * Europe as a contribution to Ralf Engelschall's mod_ssl project.
 */

/*
 * The shared-memory segment header can be cast to and from the
 * SHMCBHeader type, all other structures need to be initialised by
 * utility functions.
 *
 * The "header" looks like this;
 *
 * data applying to the overall structure:
 * - division_offset (unsigned int):
 *   how far into the shared memory segment the first division is.
 * - division_size (unsigned int):
 *   how many bytes each division occupies.
 *   (NB: This includes the queue and the cache)
 * - division_mask (unsigned char):
 *   the "mask" in the next line. Add one to this,
 *   and that's the number of divisions.
 *
 * data applying to within each division:
 * - queue_size (unsigned int):
 *   how big each "queue" is. NB: The queue is the first block in each
 *   division and is followed immediately by the cache itself so so
 *   there's no cache_offset value.
 *
 * data applying to within each queue:
 * - index_num (unsigned char):
 *   how many indexes in each cache's queue
 * - index_offset (unsigned char):
 *   how far into the queue the first index is.
 * - index_size:
 *   how big each index is.
 *
 * data applying to within each cache:
 * - cache_data_offset (unsigned int):
 *   how far into the cache the session-data array is stored.
 * - cache_data_size (unsigned int):
 *   how big each cache's data block is.
 *
 * statistics data (this will eventually be per-division but right now
 * there's only one mutex):
 * - stores (unsigned long):
 *   how many stores have been performed in the cache.
 * - expiries (unsigned long):
 *   how many session have been expired from the cache.
 * - scrolled (unsigned long):
 *   how many sessions have been scrolled out of full cache during a
 *   "store" operation. This is different to the "removes" stats as
 *   they are requested by mod_ssl/Apache, these are done because of
 *   cache logistics. (NB: Also, this value should be deducible from
 *   the others if my code has no bugs, but I count it anyway - plus
 *   it helps debugging :-).
 * - retrieves_hit (unsigned long):
 *   how many session-retrieves have succeeded.
 * - retrieves_miss (unsigned long):
 *   how many session-retrieves have failed.
 * - removes_hit (unsigned long):
 * - removes_miss (unsigned long):
 *
 * Following immediately after the header is an array of "divisions".
 * Each division is simply a "queue" immediately followed by its
 * corresponding "cache". Each division handles some pre-defined band
 * of sessions by using the "division_mask" in the header. Eg. if
 * division_mask=0x1f then there are 32 divisions, the first of which
 * will store sessions whose least-significant 5 bits are 0, the second
 * stores session whose LS 5 bits equal 1, etc. A queue is an indexing
 * structure referring to its corresponding cache.
 *
 * A "queue" looks like this;
 *
 * - first_pos (unsigned int):
 *   the location within the array of indexes where the virtual
 *   "left-hand-edge" of the cyclic buffer is.
 * - pos_count (unsigned int):
 *   the number of indexes occupied from first_pos onwards.
 *
 * ...followed by an array of indexes, each of which can be
 * memcpy'd to and from an SHMCBIndex, and look like this;
 *
 * - expires (time_t):
 *   the time() value at which this session expires.
 * - offset (unsigned int):
 *   the offset within the cache data block where the corresponding
 *   session is stored.
 * - s_id2 (unsigned char):
 *   the second byte of the session_id, stored as an optimisation to
 *   reduce the number of d2i_SSL_SESSION calls that are made when doing
 *   a lookup.
 * - removed (unsigned char):
 *   a byte used to indicate whether a session has been "passively"
 *   removed. Ie. it is still in the cache but is to be disregarded by
 *   any "retrieve" operation.
 *
 * A "cache" looks like this;
 *
 * - first_pos (unsigned int):
 *   the location within the data block where the virtual
 *   "left-hand-edge" of the cyclic buffer is.
 * - pos_count (unsigned int):
 *   the number of bytes used in the data block from first_pos onwards.
 *
 * ...followed by the data block in which actual DER-encoded SSL
 * sessions are stored.
 */

/*
 * Header - can be memcpy'd to and from the front of the shared
 * memory segment. NB: The first copy (commented out) has the
 * elements in a meaningful order, but due to data-alignment
 * braindeadness, the second (uncommented) copy has the types grouped
 * so as to decrease "struct-bloat". sigh.
 */
typedef struct {
    unsigned long num_stores;
    unsigned long num_expiries;
    unsigned long num_scrolled;
    unsigned long num_retrieves_hit;
    unsigned long num_retrieves_miss;
    unsigned long num_removes_hit;
    unsigned long num_removes_miss;
    unsigned int division_offset;
    unsigned int division_size;
    unsigned int queue_size;
    unsigned int cache_data_offset;
    unsigned int cache_data_size;
    unsigned char division_mask;
    unsigned int index_num;
    unsigned int index_offset;
    unsigned int index_size;
} SHMCBHeader;

/*
 * Index - can be memcpy'd to and from an index inside each
 * queue's index array.
 */
typedef struct {
    time_t expires;
    unsigned int offset;
    unsigned char s_id2;
    unsigned char removed;
} SHMCBIndex;

/*
 * Queue - must be populated by a call to shmcb_get_division
 * and the structure's pointers are used for updating (ie.
 * the structure doesn't need any "set" to update values).
 */
typedef struct {
    SHMCBHeader *header;
    unsigned int *first_pos;
    unsigned int *pos_count;
    SHMCBIndex *indexes;
} SHMCBQueue;

/*
 * Cache - same comment as for Queue. 'Queue's are in a 1-1
 * correspondance with 'Cache's and are usually carried round
 * in a pair, they are only seperated for clarity.
 */
typedef struct {
    SHMCBHeader *header;
    unsigned int *first_pos;
    unsigned int *pos_count;
    unsigned char *data;
} SHMCBCache;

/*
 * Forward function prototypes.
 */

/* Functions for working around data-alignment-picky systems (sparcs,
   Irix, etc). These use "memcpy" as a way of foxing these systems into
   treating the composite types as byte-arrays rather than higher-level
   primitives that it prefers to have 4-(or 8-)byte aligned. I don't
   envisage this being a performance issue as a couple of 2 or 4 byte
   memcpys can hardly make a dent on the massive memmove operations this
   cache technique avoids, nor the overheads of ASN en/decoding. */
static unsigned int shmcb_get_safe_uint(unsigned int *);
static void shmcb_set_safe_uint_ex(unsigned char *, const unsigned char *);
#define shmcb_set_safe_uint(pdest, src) \
        do { \
                unsigned int tmp_uint = src; \
                shmcb_set_safe_uint_ex((unsigned char *)pdest, \
                        (const unsigned char *)(&tmp_uint)); \
        } while(0)
#if 0 /* Unused so far */
static unsigned long shmcb_get_safe_ulong(unsigned long *);
static void shmcb_set_safe_ulong_ex(unsigned char *, const unsigned char *);
#define shmcb_set_safe_ulong(pdest, src) \
        do { \
                unsigned long tmp_ulong = src; \
                shmcb_set_safe_ulong_ex((unsigned char *)pdest, \
                        (const unsigned char *)(&tmp_ulong)); \
        } while(0)
#endif
static time_t shmcb_get_safe_time(time_t *);
static void shmcb_set_safe_time_ex(unsigned char *, const unsigned char *);
#define shmcb_set_safe_time(pdest, src) \
        do { \
                time_t tmp_time = src; \
                shmcb_set_safe_time_ex((unsigned char *)pdest, \
                        (const unsigned char *)(&tmp_time)); \
        } while(0)

/* This is used to persuade the compiler from using an inline memset()
 * which has no respect for alignment, since the size parameter is
 * often a compile-time constant.  GCC >= 4 will aggressively inline
 * static functions, so it's marked as explicitly not-inline. */
#if defined(__GNUC__) && __GNUC__ > 3
__attribute__((__noinline__))
#endif
static void shmcb_safe_clear(void *ptr, size_t size)
{
        memset(ptr, 0, size);
}

/* Underlying functions for session-caching */
static BOOL shmcb_init_memory(server_rec *, void *, unsigned int);
static BOOL shmcb_store_session(server_rec *, void *, UCHAR *, int, SSL_SESSION *, time_t);
static SSL_SESSION *shmcb_retrieve_session(server_rec *, void *, UCHAR *, int);
static BOOL shmcb_remove_session(server_rec *, void *, UCHAR *, int);

/* Utility functions for manipulating the structures */
static void shmcb_get_header(void *, SHMCBHeader **);
static BOOL shmcb_get_division(SHMCBHeader *, SHMCBQueue *, SHMCBCache *, unsigned int);
static SHMCBIndex *shmcb_get_index(const SHMCBQueue *, unsigned int);
static unsigned int shmcb_expire_division(server_rec *, SHMCBQueue *, SHMCBCache *);
static BOOL shmcb_insert_encoded_session(server_rec *, SHMCBQueue *, SHMCBCache *, unsigned char *, unsigned int, unsigned char *, time_t);
static SSL_SESSION *shmcb_lookup_session_id(server_rec *, SHMCBQueue *, SHMCBCache *, UCHAR *, unsigned int);
static BOOL shmcb_remove_session_id(server_rec *, SHMCBQueue *, SHMCBCache *, UCHAR *, unsigned int);

/*
 * Data-alignment functions (a.k.a. avoidance tactics)
 *
 * NB: On HPUX (and possibly others) there is a *very* mischievous little
 * "optimisation" in the compilers where it will convert the following;
 *      memcpy(dest_ptr, &source, sizeof(unsigned int));
 * (where dest_ptr is of type (unsigned int *) and source is (unsigned int))
 * into;
 *      *dest_ptr = source; (or *dest_ptr = *(&source), not sure).
 * Either way, it completely destroys the whole point of these _safe_
 * functions, because the assignment operation will fall victim to the
 * architecture's byte-alignment dictations, whereas the memcpy (as a
 * byte-by-byte copy) should not. sigh. So, if you're wondering about the
 * apparently unnecessary conversions to (unsigned char *) in these
 * functions, you now have an explanation. Don't just revert them back and
 * say "ooh look, it still works" - if you try it on HPUX (well, 32-bit
 * HPUX 11.00 at least) you may find it fails with a SIGBUS. :-(
 */

static unsigned int shmcb_get_safe_uint(unsigned int *ptr)
{
    unsigned int ret;
    shmcb_set_safe_uint_ex((unsigned char *)(&ret),
                    (const unsigned char *)ptr);
    return ret;
}

static void shmcb_set_safe_uint_ex(unsigned char *dest,
                                const unsigned char *src)
{
    memcpy(dest, src, sizeof(unsigned int));
}

#if 0 /* Unused so far */
static unsigned long shmcb_get_safe_ulong(unsigned long *ptr)
{
    unsigned long ret;
    shmcb_set_safe_ulong_ex((unsigned char *)(&ret),
                    (const unsigned char *)ptr);
    return ret;
}

static void shmcb_set_safe_ulong_ex(unsigned char *dest,
                                const unsigned char *src)
{
    memcpy(dest, src, sizeof(unsigned long));
}
#endif

static time_t shmcb_get_safe_time(time_t * ptr)
{
    time_t ret;
    shmcb_set_safe_time_ex((unsigned char *)(&ret),
                    (const unsigned char *)ptr);
    return ret;
}

static void shmcb_set_safe_time_ex(unsigned char *dest,
                                const unsigned char *src)
{
    memcpy(dest, src, sizeof(time_t));
}
/*
**
** High-Level "handlers" as per ssl_scache.c
**
*/

void ssl_scache_shmcb_init(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    void *shm_segment;
    apr_size_t shm_segsize;
    apr_status_t rv;

    /*
     * Create shared memory segment
     */
    if (mc->szSessionCacheDataFile == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "SSLSessionCache required");
        ssl_die();
    }

    /* Use anonymous shm by default, fall back on name-based. */
    rv = apr_shm_create(&(mc->pSessionCacheDataMM),
                        mc->nSessionCacheDataSize,
                        NULL, mc->pPool);

    if (APR_STATUS_IS_ENOTIMPL(rv)) {
        /* For a name-based segment, remove it first in case of a
         * previous unclean shutdown. */
        apr_shm_remove(mc->szSessionCacheDataFile, mc->pPool);

        rv = apr_shm_create(&(mc->pSessionCacheDataMM),
