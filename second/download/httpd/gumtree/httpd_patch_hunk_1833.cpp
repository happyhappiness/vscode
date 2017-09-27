  *  ssl_scache_shmcb.c
  *  Session Cache via Shared Memory (Cyclic Buffer Variant)
  */
 
 #include "ssl_private.h"
 
-/*
+/* 
  * This shared memory based SSL session cache implementation was
  * originally written by Geoff Thorpe <geoff geoffthorpe.net> for C2Net
  * Europe as a contribution to Ralf Engelschall's mod_ssl project.
- */
-
-/*
- * The shared-memory segment header can be cast to and from the
- * SHMCBHeader type, all other structures need to be initialised by
- * utility functions.
- *
- * The "header" looks like this;
- *
- * data applying to the overall structure:
- * - division_offset (unsigned int):
- *   how far into the shared memory segment the first division is.
- * - division_size (unsigned int):
- *   how many bytes each division occupies.
- *   (NB: This includes the queue and the cache)
- * - division_mask (unsigned char):
- *   the "mask" in the next line. Add one to this,
- *   and that's the number of divisions.
- *
- * data applying to within each division:
- * - queue_size (unsigned int):
- *   how big each "queue" is. NB: The queue is the first block in each
- *   division and is followed immediately by the cache itself so so
- *   there's no cache_offset value.
- *
- * data applying to within each queue:
- * - index_num (unsigned char):
- *   how many indexes in each cache's queue
- * - index_offset (unsigned char):
- *   how far into the queue the first index is.
- * - index_size:
- *   how big each index is.
- *
- * data applying to within each cache:
- * - cache_data_offset (unsigned int):
- *   how far into the cache the session-data array is stored.
- * - cache_data_size (unsigned int):
- *   how big each cache's data block is.
- *
- * statistics data (this will eventually be per-division but right now
- * there's only one mutex):
- * - stores (unsigned long):
- *   how many stores have been performed in the cache.
- * - expiries (unsigned long):
- *   how many session have been expired from the cache.
- * - scrolled (unsigned long):
- *   how many sessions have been scrolled out of full cache during a
- *   "store" operation. This is different to the "removes" stats as
- *   they are requested by mod_ssl/Apache, these are done because of
- *   cache logistics. (NB: Also, this value should be deducible from
- *   the others if my code has no bugs, but I count it anyway - plus
- *   it helps debugging :-).
- * - retrieves_hit (unsigned long):
- *   how many session-retrieves have succeeded.
- * - retrieves_miss (unsigned long):
- *   how many session-retrieves have failed.
- * - removes_hit (unsigned long):
- * - removes_miss (unsigned long):
- *
- * Following immediately after the header is an array of "divisions".
- * Each division is simply a "queue" immediately followed by its
- * corresponding "cache". Each division handles some pre-defined band
- * of sessions by using the "division_mask" in the header. Eg. if
- * division_mask=0x1f then there are 32 divisions, the first of which
- * will store sessions whose least-significant 5 bits are 0, the second
- * stores session whose LS 5 bits equal 1, etc. A queue is an indexing
- * structure referring to its corresponding cache.
- *
- * A "queue" looks like this;
  *
- * - first_pos (unsigned int):
- *   the location within the array of indexes where the virtual
- *   "left-hand-edge" of the cyclic buffer is.
- * - pos_count (unsigned int):
- *   the number of indexes occupied from first_pos onwards.
- *
- * ...followed by an array of indexes, each of which can be
- * memcpy'd to and from an SHMCBIndex, and look like this;
- *
- * - expires (time_t):
- *   the time() value at which this session expires.
- * - offset (unsigned int):
- *   the offset within the cache data block where the corresponding
- *   session is stored.
- * - s_id2 (unsigned char):
- *   the second byte of the session_id, stored as an optimisation to
- *   reduce the number of d2i_SSL_SESSION calls that are made when doing
- *   a lookup.
- * - removed (unsigned char):
- *   a byte used to indicate whether a session has been "passively"
- *   removed. Ie. it is still in the cache but is to be disregarded by
- *   any "retrieve" operation.
- *
- * A "cache" looks like this;
- *
- * - first_pos (unsigned int):
- *   the location within the data block where the virtual
- *   "left-hand-edge" of the cyclic buffer is.
- * - pos_count (unsigned int):
- *   the number of bytes used in the data block from first_pos onwards.
- *
- * ...followed by the data block in which actual DER-encoded SSL
- * sessions are stored.
+ * Since rewritten by GT to not use alignment-fudging memcpys and reduce
+ * complexity.
  */
 
 /*
- * Header - can be memcpy'd to and from the front of the shared
- * memory segment. NB: The first copy (commented out) has the
- * elements in a meaningful order, but due to data-alignment
- * braindeadness, the second (uncommented) copy has the types grouped
- * so as to decrease "struct-bloat". sigh.
+ * Header structure - the start of the shared-mem segment
  */
 typedef struct {
-    unsigned long num_stores;
-    unsigned long num_expiries;
-    unsigned long num_scrolled;
-    unsigned long num_retrieves_hit;
-    unsigned long num_retrieves_miss;
-    unsigned long num_removes_hit;
-    unsigned long num_removes_miss;
-    unsigned int division_offset;
-    unsigned int division_size;
-    unsigned int queue_size;
-    unsigned int cache_data_offset;
-    unsigned int cache_data_size;
-    unsigned char division_mask;
+    /* Stats for cache operations */
+    unsigned long stat_stores;
+    unsigned long stat_expiries;
+    unsigned long stat_scrolled;
+    unsigned long stat_retrieves_hit;
+    unsigned long stat_retrieves_miss;
+    unsigned long stat_removes_hit;
+    unsigned long stat_removes_miss;
+    /* Number of subcaches */
+    unsigned int subcache_num;
+    /* How many indexes each subcache's queue has */
     unsigned int index_num;
-    unsigned int index_offset;
-    unsigned int index_size;
+    /* How large each subcache is, including the queue and data */
+    unsigned int subcache_size;
+    /* How far into each subcache the data area is (optimisation) */
+    unsigned int subcache_data_offset;
+    /* How large the data area in each subcache is (optimisation) */
+    unsigned int subcache_data_size;
 } SHMCBHeader;
 
-/*
- * Index - can be memcpy'd to and from an index inside each
- * queue's index array.
+/* 
+ * Subcache structure - the start of each subcache, followed by
+ * indexes then data
  */
 typedef struct {
+    /* The start position and length of the cyclic buffer of indexes */
+    unsigned int idx_pos, idx_used;
+    /* Same for the data area */
+    unsigned int data_pos, data_used;
+} SHMCBSubcache;
+
+/* 
+ * Index structure - each subcache has an array of these
+ */
+typedef struct {
+    /* absolute time this entry expires */
     time_t expires;
-    unsigned int offset;
+    /* location within the subcache's data area */
+    unsigned int data_pos;
+    /* size (most logic ignores this, we keep it only to minimise memcpy) */
+    unsigned int data_used;
+    /* Optimisation to prevent ASN decoding unless a match is likely */
     unsigned char s_id2;
+    /* Used to mark explicitly-removed sessions */
     unsigned char removed;
 } SHMCBIndex;
 
-/*
- * Queue - must be populated by a call to shmcb_get_division
- * and the structure's pointers are used for updating (ie.
- * the structure doesn't need any "set" to update values).
- */
-typedef struct {
-    SHMCBHeader *header;
-    unsigned int *first_pos;
-    unsigned int *pos_count;
-    SHMCBIndex *indexes;
-} SHMCBQueue;
-
-/*
- * Cache - same comment as for Queue. 'Queue's are in a 1-1
- * correspondance with 'Cache's and are usually carried round
- * in a pair, they are only seperated for clarity.
- */
-typedef struct {
-    SHMCBHeader *header;
-    unsigned int *first_pos;
-    unsigned int *pos_count;
-    unsigned char *data;
-} SHMCBCache;
 
-/*
- * Forward function prototypes.
+/* The SHM data segment is of fixed size and stores data as follows.
+ *
+ *   [ SHMCBHeader | Subcaches ]
+ *
+ * The SHMCBHeader header structure stores metadata concerning the
+ * cache and the contained subcaches.
+ *
+ * Subcaches is a hash table of header->subcache_num SHMCBSubcache
+ * structures.  The hash table is indexed by SHMCB_MASK(id). Each
+ * SHMCBSubcache structure has a fixed size (header->subcache_size),
+ * which is determined at creation time, and looks like the following:
+ *
+ *   [ SHMCBSubcache | Indexes | Data ]
+ *
+ * Each subcache is prefixed by the SHMCBSubcache structure.
+ *
+ * The subcache's "Data" segment is a single cyclic data buffer, of
+ * total size header->subcache_data_size; data inside is referenced
+ * using byte offsets. The offset marking the beginning of the cyclic
+ * buffer is subcache->data_pos the buffer's length is
+ * subcache->data_used.
+ *
+ * "Indexes" is an array of header->index_num SHMCBIndex structures,
+ * which is used as a cyclic queue; subcache->idx_pos gives the array
+ * index of the first in use, subcache->idx_used gives the number in
+ * use.  Both ->idx_* values have a range of [0, header->index_num)
+ *
+ * Each in-use SHMCBIndex structure represents a single SSL session.
  */
 
-/* Functions for working around data-alignment-picky systems (sparcs,
-   Irix, etc). These use "memcpy" as a way of foxing these systems into
-   treating the composite types as byte-arrays rather than higher-level
-   primitives that it prefers to have 4-(or 8-)byte aligned. I don't
-   envisage this being a performance issue as a couple of 2 or 4 byte
-   memcpys can hardly make a dent on the massive memmove operations this
-   cache technique avoids, nor the overheads of ASN en/decoding. */
-static unsigned int shmcb_get_safe_uint(unsigned int *);
-static void shmcb_set_safe_uint_ex(unsigned char *, const unsigned char *);
-#define shmcb_set_safe_uint(pdest, src) \
-        do { \
-                unsigned int tmp_uint = src; \
-                shmcb_set_safe_uint_ex((unsigned char *)pdest, \
-                        (const unsigned char *)(&tmp_uint)); \
-        } while(0)
-#if 0 /* Unused so far */
-static unsigned long shmcb_get_safe_ulong(unsigned long *);
-static void shmcb_set_safe_ulong_ex(unsigned char *, const unsigned char *);
-#define shmcb_set_safe_ulong(pdest, src) \
-        do { \
-                unsigned long tmp_ulong = src; \
-                shmcb_set_safe_ulong_ex((unsigned char *)pdest, \
-                        (const unsigned char *)(&tmp_ulong)); \
-        } while(0)
-#endif
-static time_t shmcb_get_safe_time(time_t *);
-static void shmcb_set_safe_time_ex(unsigned char *, const unsigned char *);
-#define shmcb_set_safe_time(pdest, src) \
-        do { \
-                time_t tmp_time = src; \
-                shmcb_set_safe_time_ex((unsigned char *)pdest, \
-                        (const unsigned char *)(&tmp_time)); \
-        } while(0)
-
-/* This is used to persuade the compiler from using an inline memset()
- * which has no respect for alignment, since the size parameter is
- * often a compile-time constant.  GCC >= 4 will aggressively inline
- * static functions, so it's marked as explicitly not-inline. */
-#if defined(__GNUC__) && __GNUC__ > 3
-__attribute__((__noinline__))
-#endif
-static void shmcb_safe_clear(void *ptr, size_t size)
-{
-        memset(ptr, 0, size);
-}
-
-/* Underlying functions for session-caching */
-static BOOL shmcb_init_memory(server_rec *, void *, unsigned int);
-static BOOL shmcb_store_session(server_rec *, void *, UCHAR *, int, SSL_SESSION *, time_t);
-static SSL_SESSION *shmcb_retrieve_session(server_rec *, void *, UCHAR *, int);
-static BOOL shmcb_remove_session(server_rec *, void *, UCHAR *, int);
-
-/* Utility functions for manipulating the structures */
-static void shmcb_get_header(void *, SHMCBHeader **);
-static BOOL shmcb_get_division(SHMCBHeader *, SHMCBQueue *, SHMCBCache *, unsigned int);
-static SHMCBIndex *shmcb_get_index(const SHMCBQueue *, unsigned int);
-static unsigned int shmcb_expire_division(server_rec *, SHMCBQueue *, SHMCBCache *);
-static BOOL shmcb_insert_encoded_session(server_rec *, SHMCBQueue *, SHMCBCache *, unsigned char *, unsigned int, unsigned char *, time_t);
-static SSL_SESSION *shmcb_lookup_session_id(server_rec *, SHMCBQueue *, SHMCBCache *, UCHAR *, unsigned int);
-static BOOL shmcb_remove_session_id(server_rec *, SHMCBQueue *, SHMCBCache *, UCHAR *, unsigned int);
+/* This macro takes a pointer to the header and a zero-based index and returns
+ * a pointer to the corresponding subcache. */
+#define SHMCB_SUBCACHE(pHeader, num) \
+                (SHMCBSubcache *)(((unsigned char *)(pHeader)) + \
+                        sizeof(SHMCBHeader) + \
+                        (num) * ((pHeader)->subcache_size))
+
+/* This macro takes a pointer to the header and a session id and returns a
+ * pointer to the corresponding subcache. */
+#define SHMCB_MASK(pHeader, id) \
+                SHMCB_SUBCACHE((pHeader), *(id) & ((pHeader)->subcache_num - 1))
+
+/* This macro takes the same params as the last, generating two outputs for use
+ * in ap_log_error(...). */
+#define SHMCB_MASK_DBG(pHeader, id) \
+                *(id), (*(id) & ((pHeader)->subcache_num - 1))
+
+/* This macro takes a pointer to a subcache and a zero-based index and returns
+ * a pointer to the corresponding SHMCBIndex. */
+#define SHMCB_INDEX(pSubcache, num) \
+                ((SHMCBIndex *)(((unsigned char *)pSubcache) + \
+                                sizeof(SHMCBSubcache)) + num)
+
+/* This macro takes a pointer to the header and a subcache and returns a
+ * pointer to the corresponding data area. */
+#define SHMCB_DATA(pHeader, pSubcache) \
+                ((unsigned char *)(pSubcache) + (pHeader)->subcache_data_offset)
 
 /*
- * Data-alignment functions (a.k.a. avoidance tactics)
- *
- * NB: On HPUX (and possibly others) there is a *very* mischievous little
- * "optimisation" in the compilers where it will convert the following;
- *      memcpy(dest_ptr, &source, sizeof(unsigned int));
- * (where dest_ptr is of type (unsigned int *) and source is (unsigned int))
- * into;
- *      *dest_ptr = source; (or *dest_ptr = *(&source), not sure).
- * Either way, it completely destroys the whole point of these _safe_
- * functions, because the assignment operation will fall victim to the
- * architecture's byte-alignment dictations, whereas the memcpy (as a
- * byte-by-byte copy) should not. sigh. So, if you're wondering about the
- * apparently unnecessary conversions to (unsigned char *) in these
- * functions, you now have an explanation. Don't just revert them back and
- * say "ooh look, it still works" - if you try it on HPUX (well, 32-bit
- * HPUX 11.00 at least) you may find it fails with a SIGBUS. :-(
+ * Cyclic functions - assists in "wrap-around"/modulo logic
  */
 
-static unsigned int shmcb_get_safe_uint(unsigned int *ptr)
-{
-    unsigned int ret;
-    shmcb_set_safe_uint_ex((unsigned char *)(&ret),
-                    (const unsigned char *)ptr);
-    return ret;
-}
-
-static void shmcb_set_safe_uint_ex(unsigned char *dest,
-                                const unsigned char *src)
+/* Addition modulo 'mod' */
+#define SHMCB_CYCLIC_INCREMENT(val,inc,mod) \
+                (((val) + (inc)) % (mod))
+
+/* Subtraction (or "distance between") modulo 'mod' */
+#define SHMCB_CYCLIC_SPACE(val1,val2,mod) \
+                ((val2) >= (val1) ? ((val2) - (val1)) : \
+                        ((val2) + (mod) - (val1)))
+
+/* A "normal-to-cyclic" memcpy. */
+static void shmcb_cyclic_ntoc_memcpy(unsigned int buf_size, unsigned char *data,
+                                     unsigned int dest_offset, unsigned char *src,
+                                     unsigned int src_len)
 {
-    memcpy(dest, src, sizeof(unsigned int));
-}
-
-#if 0 /* Unused so far */
-static unsigned long shmcb_get_safe_ulong(unsigned long *ptr)
-{
-    unsigned long ret;
-    shmcb_set_safe_ulong_ex((unsigned char *)(&ret),
-                    (const unsigned char *)ptr);
-    return ret;
+    if (dest_offset + src_len < buf_size)
+        /* It be copied all in one go */
+        memcpy(data + dest_offset, src, src_len);
+    else {
+        /* Copy the two splits */
+        memcpy(data + dest_offset, src, buf_size - dest_offset);
+        memcpy(data, src + buf_size - dest_offset,
+               src_len + dest_offset - buf_size);
+    }
 }
 
-static void shmcb_set_safe_ulong_ex(unsigned char *dest,
-                                const unsigned char *src)
+/* A "cyclic-to-normal" memcpy. */
+static void shmcb_cyclic_cton_memcpy(unsigned int buf_size, unsigned char *dest,
+                                     unsigned char *data, unsigned int src_offset,
+                                     unsigned int src_len)
 {
-    memcpy(dest, src, sizeof(unsigned long));
+    if (src_offset + src_len < buf_size)
+        /* It be copied all in one go */
+        memcpy(dest, data + src_offset, src_len);
+    else {
+        /* Copy the two splits */
+        memcpy(dest, data + src_offset, buf_size - src_offset);
+        memcpy(dest + buf_size - src_offset, data,
+               src_len + src_offset - buf_size);
+    }
 }
-#endif
 
-static time_t shmcb_get_safe_time(time_t * ptr)
-{
-    time_t ret;
-    shmcb_set_safe_time_ex((unsigned char *)(&ret),
-                    (const unsigned char *)ptr);
-    return ret;
-}
+/* Prototypes for low-level subcache operations */
+static void shmcb_subcache_expire(server_rec *, SHMCBHeader *, SHMCBSubcache *);
+static BOOL shmcb_subcache_store(server_rec *, SHMCBHeader *, SHMCBSubcache *,
+                                 UCHAR *, unsigned int, UCHAR *, time_t);
+static SSL_SESSION *shmcb_subcache_retrieve(server_rec *, SHMCBHeader *, SHMCBSubcache *,
+                                            UCHAR *, unsigned int);
+static BOOL shmcb_subcache_remove(server_rec *, SHMCBHeader *, SHMCBSubcache *,
+                                 UCHAR *, unsigned int);
 
-static void shmcb_set_safe_time_ex(unsigned char *dest,
-                                const unsigned char *src)
-{
-    memcpy(dest, src, sizeof(time_t));
-}
 /*
-**
-** High-Level "handlers" as per ssl_scache.c
-**
-*/
+ * High-Level "handlers" as per ssl_scache.c
+ * subcache internals are deferred to shmcb_subcache_*** functions lower down
+ */
 
 void ssl_scache_shmcb_init(server_rec *s, apr_pool_t *p)
 {
     SSLModConfigRec *mc = myModConfig(s);
     void *shm_segment;
     apr_size_t shm_segsize;
     apr_status_t rv;
+    SHMCBHeader *header;
+    unsigned int num_subcache, num_idx, loop;
 
-    /*
-     * Create shared memory segment
-     */
+    /* Create shared memory segment */
     if (mc->szSessionCacheDataFile == NULL) {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                      "SSLSessionCache required");
         ssl_die();
     }
 
     /* Use anonymous shm by default, fall back on name-based. */
-    rv = apr_shm_create(&(mc->pSessionCacheDataMM),
-                        mc->nSessionCacheDataSize,
+    rv = apr_shm_create(&(mc->pSessionCacheDataMM), 
+                        mc->nSessionCacheDataSize, 
                         NULL, mc->pPool);
-
     if (APR_STATUS_IS_ENOTIMPL(rv)) {
         /* For a name-based segment, remove it first in case of a
          * previous unclean shutdown. */
         apr_shm_remove(mc->szSessionCacheDataFile, mc->pPool);
 
         rv = apr_shm_create(&(mc->pSessionCacheDataMM),
