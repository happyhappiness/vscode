 *  ssl_scache_shmcb.c
 *  Session Cache via Shared Memory (Cyclic Buffer Variant)
 */

#include "ssl_private.h"

/* 
 * This shared memory based SSL session cache implementation was
 * originally written by Geoff Thorpe <geoff geoffthorpe.net> for C2Net
 * Europe as a contribution to Ralf Engelschall's mod_ssl project.
 *
 * Since rewritten by GT to not use alignment-fudging memcpys and reduce
 * complexity.
 */

/*
 * Header structure - the start of the shared-mem segment
 */
typedef struct {
    /* Stats for cache operations */
    unsigned long stat_stores;
    unsigned long stat_expiries;
    unsigned long stat_scrolled;
    unsigned long stat_retrieves_hit;
    unsigned long stat_retrieves_miss;
    unsigned long stat_removes_hit;
    unsigned long stat_removes_miss;
    /* Number of subcaches */
    unsigned int subcache_num;
    /* How many indexes each subcache's queue has */
    unsigned int index_num;
    /* How large each subcache is, including the queue and data */
    unsigned int subcache_size;
    /* How far into each subcache the data area is (optimisation) */
    unsigned int subcache_data_offset;
    /* How large the data area in each subcache is (optimisation) */
    unsigned int subcache_data_size;
} SHMCBHeader;

/* 
 * Subcache structure - the start of each subcache, followed by
 * indexes then data
 */
typedef struct {
    /* The start position and length of the cyclic buffer of indexes */
    unsigned int idx_pos, idx_used;
    /* Same for the data area */
    unsigned int data_pos, data_used;
} SHMCBSubcache;

/* 
 * Index structure - each subcache has an array of these
 */
typedef struct {
    /* absolute time this entry expires */
    time_t expires;
    /* location within the subcache's data area */
    unsigned int data_pos;
    /* size (most logic ignores this, we keep it only to minimise memcpy) */
    unsigned int data_used;
    /* Optimisation to prevent ASN decoding unless a match is likely */
    unsigned char s_id2;
    /* Used to mark explicitly-removed sessions */
    unsigned char removed;
} SHMCBIndex;


/* The SHM data segment is of fixed size and stores data as follows.
 *
 *   [ SHMCBHeader | Subcaches ]
 *
 * The SHMCBHeader header structure stores metadata concerning the
 * cache and the contained subcaches.
 *
 * Subcaches is a hash table of header->subcache_num SHMCBSubcache
 * structures.  The hash table is indexed by SHMCB_MASK(id). Each
 * SHMCBSubcache structure has a fixed size (header->subcache_size),
 * which is determined at creation time, and looks like the following:
 *
 *   [ SHMCBSubcache | Indexes | Data ]
 *
 * Each subcache is prefixed by the SHMCBSubcache structure.
 *
 * The subcache's "Data" segment is a single cyclic data buffer, of
 * total size header->subcache_data_size; data inside is referenced
 * using byte offsets. The offset marking the beginning of the cyclic
 * buffer is subcache->data_pos the buffer's length is
 * subcache->data_used.
 *
 * "Indexes" is an array of header->index_num SHMCBIndex structures,
 * which is used as a cyclic queue; subcache->idx_pos gives the array
 * index of the first in use, subcache->idx_used gives the number in
 * use.  Both ->idx_* values have a range of [0, header->index_num)
 *
 * Each in-use SHMCBIndex structure represents a single SSL session.
 */

/* This macro takes a pointer to the header and a zero-based index and returns
 * a pointer to the corresponding subcache. */
#define SHMCB_SUBCACHE(pHeader, num) \
                (SHMCBSubcache *)(((unsigned char *)(pHeader)) + \
                        sizeof(SHMCBHeader) + \
                        (num) * ((pHeader)->subcache_size))

/* This macro takes a pointer to the header and a session id and returns a
 * pointer to the corresponding subcache. */
#define SHMCB_MASK(pHeader, id) \
                SHMCB_SUBCACHE((pHeader), *(id) & ((pHeader)->subcache_num - 1))

/* This macro takes the same params as the last, generating two outputs for use
 * in ap_log_error(...). */
#define SHMCB_MASK_DBG(pHeader, id) \
                *(id), (*(id) & ((pHeader)->subcache_num - 1))

/* This macro takes a pointer to a subcache and a zero-based index and returns
 * a pointer to the corresponding SHMCBIndex. */
#define SHMCB_INDEX(pSubcache, num) \
                ((SHMCBIndex *)(((unsigned char *)pSubcache) + \
                                sizeof(SHMCBSubcache)) + num)

/* This macro takes a pointer to the header and a subcache and returns a
 * pointer to the corresponding data area. */
#define SHMCB_DATA(pHeader, pSubcache) \
                ((unsigned char *)(pSubcache) + (pHeader)->subcache_data_offset)

/*
 * Cyclic functions - assists in "wrap-around"/modulo logic
 */

/* Addition modulo 'mod' */
#define SHMCB_CYCLIC_INCREMENT(val,inc,mod) \
                (((val) + (inc)) % (mod))

/* Subtraction (or "distance between") modulo 'mod' */
#define SHMCB_CYCLIC_SPACE(val1,val2,mod) \
                ((val2) >= (val1) ? ((val2) - (val1)) : \
                        ((val2) + (mod) - (val1)))

/* A "normal-to-cyclic" memcpy. */
static void shmcb_cyclic_ntoc_memcpy(unsigned int buf_size, unsigned char *data,
                                     unsigned int dest_offset, unsigned char *src,
                                     unsigned int src_len)
{
    if (dest_offset + src_len < buf_size)
        /* It be copied all in one go */
        memcpy(data + dest_offset, src, src_len);
    else {
        /* Copy the two splits */
        memcpy(data + dest_offset, src, buf_size - dest_offset);
        memcpy(data, src + buf_size - dest_offset,
               src_len + dest_offset - buf_size);
    }
}

/* A "cyclic-to-normal" memcpy. */
static void shmcb_cyclic_cton_memcpy(unsigned int buf_size, unsigned char *dest,
                                     unsigned char *data, unsigned int src_offset,
                                     unsigned int src_len)
{
    if (src_offset + src_len < buf_size)
        /* It be copied all in one go */
        memcpy(dest, data + src_offset, src_len);
    else {
        /* Copy the two splits */
        memcpy(dest, data + src_offset, buf_size - src_offset);
        memcpy(dest + buf_size - src_offset, data,
               src_len + src_offset - buf_size);
    }
}

/* Prototypes for low-level subcache operations */
static void shmcb_subcache_expire(server_rec *, SHMCBHeader *, SHMCBSubcache *);
static BOOL shmcb_subcache_store(server_rec *, SHMCBHeader *, SHMCBSubcache *,
                                 UCHAR *, unsigned int, UCHAR *, time_t);
static SSL_SESSION *shmcb_subcache_retrieve(server_rec *, SHMCBHeader *, SHMCBSubcache *,
                                            UCHAR *, unsigned int);
static BOOL shmcb_subcache_remove(server_rec *, SHMCBHeader *, SHMCBSubcache *,
                                 UCHAR *, unsigned int);

/*
 * High-Level "handlers" as per ssl_scache.c
 * subcache internals are deferred to shmcb_subcache_*** functions lower down
 */

void ssl_scache_shmcb_init(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    void *shm_segment;
    apr_size_t shm_segsize;
    apr_status_t rv;
    SHMCBHeader *header;
    unsigned int num_subcache, num_idx, loop;

    /* Create shared memory segment */
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
