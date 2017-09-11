@@ -17,6 +17,7 @@ struct RedisModule {
     char *name;     /* Module name. */
     int ver;        /* Module version. We use just progressive integers. */
     int apiver;     /* Module API version as requested during initialization.*/
+    list *types;    /* Module data types. */
 };
 typedef struct RedisModule RedisModule;
 
@@ -35,6 +36,29 @@ struct AutoMemEntry {
 #define REDISMODULE_AM_REPLY 2
 #define REDISMODULE_AM_FREED 3 /* Explicitly freed by user already. */
 
+/* The pool allocator block. Redis Modules can allocate memory via this special
+ * allocator that will automatically release it all once the callback returns.
+ * This means that it can only be used for ephemeral allocations. However
+ * there are two advantages for modules to use this API:
+ *
+ * 1) The memory is automatically released when the callback returns.
+ * 2) This allocator is faster for many small allocations since whole blocks
+ *    are allocated, and small pieces returned to the caller just advancing
+ *    the index of the allocation.
+ *
+ * Allocations are always rounded to the size of the void pointer in order
+ * to always return aligned memory chunks. */
+
+#define REDISMODULE_POOL_ALLOC_MIN_SIZE (1024*8)
+#define REDISMODULE_POOL_ALLOC_ALIGN (sizeof(void*))
+
+typedef struct RedisModulePoolAllocBlock {
+    uint32_t size;
+    uint32_t used;
+    struct RedisModulePoolAllocBlock *next;
+    char memory[];
+} RedisModulePoolAllocBlock;
+
 /* This structure represents the context in which Redis modules operate.
  * Most APIs module can access, get a pointer to the context, so that the API
  * implementation can hold state across calls, or remember what to free after
@@ -56,10 +80,12 @@ struct RedisModuleCtx {
     /* Used if there is the REDISMODULE_CTX_KEYS_POS_REQUEST flag set. */
     int *keys_pos;
     int keys_count;
+
+    struct RedisModulePoolAllocBlock *pa_head;
 };
 typedef struct RedisModuleCtx RedisModuleCtx;
 
-#define REDISMODULE_CTX_INIT {(void*)(unsigned long)&RM_GetApi, NULL, NULL, NULL, 0, 0, 0, NULL, 0, NULL, 0}
+#define REDISMODULE_CTX_INIT {(void*)(unsigned long)&RM_GetApi, NULL, NULL, NULL, 0, 0, 0, NULL, 0, NULL, 0, NULL}
 #define REDISMODULE_CTX_MULTI_EMITTED (1<<0)
 #define REDISMODULE_CTX_AUTO_MEMORY (1<<1)
 #define REDISMODULE_CTX_KEYS_POS_REQUEST (1<<2)
@@ -111,7 +137,7 @@ typedef struct RedisModuleCommandProxy RedisModuleCommandProxy;
 /* Reply of RM_Call() function. The function is filled in a lazy
  * way depending on the function called on the reply structure. By default
  * only the type, proto and protolen are filled. */
-struct RedisModuleCallReply {
+typedef struct RedisModuleCallReply {
     RedisModuleCtx *ctx;
     int type;       /* REDISMODULE_REPLY_... */
     int flags;      /* REDISMODULE_REPLYFLAG_...  */
@@ -126,8 +152,7 @@ struct RedisModuleCallReply {
         long long ll;    /* Reply value for integer reply. */
         struct RedisModuleCallReply *array; /* Array of sub-reply elements. */
     } val;
-};
-typedef struct RedisModuleCallReply RedisModuleCallReply;
+} RedisModuleCallReply;
 
 /* --------------------------------------------------------------------------
  * Prototypes
@@ -138,7 +163,103 @@ void RM_CloseKey(RedisModuleKey *key);
 void autoMemoryCollect(RedisModuleCtx *ctx);
 robj **moduleCreateArgvFromUserFormat(const char *cmdname, const char *fmt, int *argcp, int *flags, va_list ap);
 void moduleReplicateMultiIfNeeded(RedisModuleCtx *ctx);
-void RM_ZsetRangeStop(RedisModuleKey *key);
+void RM_ZsetRangeStop(RedisModuleKey *kp);
+static void zsetKeyReset(RedisModuleKey *key);
+
+/* --------------------------------------------------------------------------
+ * Heap allocation raw functions
+ * -------------------------------------------------------------------------- */
+
+/* Use like malloc(). Memory allocated with this function is reported in
+ * Redis INFO memory, used for keys eviction according to maxmemory settings
+ * and in general is taken into account as memory allocated by Redis.
+ * You should avoid using malloc(). */
+void *RM_Alloc(size_t bytes) {
+    return zmalloc(bytes);
+}
+
+/* Use like calloc(). Memory allocated with this function is reported in
+ * Redis INFO memory, used for keys eviction according to maxmemory settings
+ * and in general is taken into account as memory allocated by Redis.
+ * You should avoid using calloc() directly. */
+void *RM_Calloc(size_t nmemb, size_t size) {
+    return zcalloc(nmemb*size);
+}
+
+/* Use like realloc() for memory obtained with RedisModule_Alloc(). */
+void* RM_Realloc(void *ptr, size_t bytes) {
+    return zrealloc(ptr,bytes);
+}
+
+/* Use like free() for memory obtained by RedisModule_Alloc() and
+ * RedisModule_Realloc(). However you should never try to free with
+ * RedisModule_Free() memory allocated with malloc() inside your module. */
+void RM_Free(void *ptr) {
+    zfree(ptr);
+}
+
+/* Like strdup() but returns memory allocated with RedisModule_Alloc(). */
+char *RM_Strdup(const char *str) {
+    return zstrdup(str);
+}
+
+/* --------------------------------------------------------------------------
+ * Pool allocator
+ * -------------------------------------------------------------------------- */
+
+/* Release the chain of blocks used for pool allocations. */
+void poolAllocRelease(RedisModuleCtx *ctx) {
+    RedisModulePoolAllocBlock *head = ctx->pa_head, *next;
+
+    while(head != NULL) {
+        next = head->next;
+        zfree(head);
+        head = next;
+    }
+    ctx->pa_head = NULL;
+}
+
+/* Return heap allocated memory that will be freed automatically when the
+ * module callback function returns. Mostly suitable for small allocations
+ * that are short living and must be released when the callback returns
+ * anyway. The returned memory is aligned to the architecture word size
+ * if at least word size bytes are requested, otherwise it is just
+ * aligned to the next power of two, so for example a 3 bytes request is
+ * 4 bytes aligned while a 2 bytes request is 2 bytes aligned.
+ *
+ * There is no realloc style function since when this is needed to use the
+ * pool allocator is not a good idea.
+ *
+ * The function returns NULL if `bytes` is 0. */
+void *RM_PoolAlloc(RedisModuleCtx *ctx, size_t bytes) {
+    if (bytes == 0) return NULL;
+    RedisModulePoolAllocBlock *b = ctx->pa_head;
+    size_t left = b ? b->size - b->used : 0;
+
+    /* Fix alignment. */
+    if (left >= bytes) {
+        size_t alignment = REDISMODULE_POOL_ALLOC_ALIGN;
+        while (bytes < alignment && alignment/2 >= bytes) alignment /= 2;
+        if (b->used % alignment)
+            b->used += alignment - (b->used % alignment);
+        left = (b->used > b->size) ? 0 : b->size - b->used;
+    }
+
+    /* Create a new block if needed. */
+    if (left < bytes) {
+        size_t blocksize = REDISMODULE_POOL_ALLOC_MIN_SIZE;
+        if (blocksize < bytes) blocksize = bytes;
+        b = zmalloc(sizeof(*b) + blocksize);
+        b->size = blocksize;
+        b->used = 0;
+        b->next = ctx->pa_head;
+        ctx->pa_head = b;
+    }
+
+    char *retval = b->memory + b->used;
+    b->used += bytes;
+    return retval;
+}
 
 /* --------------------------------------------------------------------------
  * Helpers for modules API implementation
@@ -240,6 +361,7 @@ int RM_GetApi(const char *funcname, void **targetPtrPtr) {
 /* Free the context after the user function was called. */
 void moduleFreeContext(RedisModuleCtx *ctx) {
     autoMemoryCollect(ctx);
+    poolAllocRelease(ctx);
     if (ctx->postponed_arrays) {
         zfree(ctx->postponed_arrays);
         ctx->postponed_arrays_count = 0;
@@ -463,6 +585,7 @@ void RM_SetModuleAttribs(RedisModuleCtx *ctx, const char *name, int ver, int api
     module->name = sdsnew((char*)name);
     module->ver = ver;
     module->apiver = apiver;
+    module->types = listCreate();
     ctx->module = module;
 }
 
@@ -496,15 +619,28 @@ void autoMemoryAdd(RedisModuleCtx *ctx, int type, void *ptr) {
 void autoMemoryFreed(RedisModuleCtx *ctx, int type, void *ptr) {
     if (!(ctx->flags & REDISMODULE_CTX_AUTO_MEMORY)) return;
 
-    int j;
-    for (j = 0; j < ctx->amqueue_used; j++) {
-        if (ctx->amqueue[j].type == type &&
-            ctx->amqueue[j].ptr == ptr)
-        {
-            ctx->amqueue[j].type = REDISMODULE_AM_FREED;
-            /* Optimization: if this is the last element, we can
-             * reuse it. */
-            if (j == ctx->amqueue_used-1) ctx->amqueue_used--;
+    int count = (ctx->amqueue_used+1)/2;
+    for (int j = 0; j < count; j++) {
+        for (int side = 0; side < 2; side++) {
+            /* For side = 0 check right side of the array, for
+             * side = 1 check the left side instead (zig-zag scanning). */
+            int i = (side == 0) ? (ctx->amqueue_used - 1 - j) : j;
+            if (ctx->amqueue[i].type == type &&
+                ctx->amqueue[i].ptr == ptr)
+            {
+                ctx->amqueue[i].type = REDISMODULE_AM_FREED;
+
+                /* Switch the freed element and the last element, to avoid growing
+                 * the queue unnecessarily if we allocate/free in a loop */
+                if (i != ctx->amqueue_used-1) {
+                    ctx->amqueue[i] = ctx->amqueue[ctx->amqueue_used-1];
+                }
+
+                /* Reduce the size of the queue because we either moved the top
+                 * element elsewhere or freed it */
+                ctx->amqueue_used--;
+                return;
+            }
         }
     }
 }
@@ -559,6 +695,17 @@ RedisModuleString *RM_CreateStringFromLongLong(RedisModuleCtx *ctx, long long ll
     return RM_CreateString(ctx,buf,len);
 }
 
+/* Like RedisModule_CreatString(), but creates a string starting from another
+ * RedisModuleString.
+ *
+ * The returned string must be released with RedisModule_FreeString() or by
+ * enabling automatic memory management. */
+RedisModuleString *RM_CreateStringFromString(RedisModuleCtx *ctx, const RedisModuleString *str) {
+    RedisModuleString *o = dupStringObject(str);
+    autoMemoryAdd(ctx,REDISMODULE_AM_STRING,o);
+    return o;
+}
+
 /* Free a module string object obtained with one of the Redis modules API calls
  * that return new string objects.
  *
@@ -573,7 +720,7 @@ void RM_FreeString(RedisModuleCtx *ctx, RedisModuleString *str) {
 /* Given a string module object, this function returns the string pointer
  * and length of the string. The returned pointer and length should only
  * be used for read only accesses and never modified. */
-const char *RM_StringPtrLen(RedisModuleString *str, size_t *len) {
+const char *RM_StringPtrLen(const RedisModuleString *str, size_t *len) {
     if (len) *len = sdslen(str->ptr);
     return str->ptr;
 }
@@ -582,15 +729,15 @@ const char *RM_StringPtrLen(RedisModuleString *str, size_t *len) {
  * Returns REDISMODULE_OK on success. If the string can't be parsed
  * as a valid, strict long long (no spaces before/after), REDISMODULE_ERR
  * is returned. */
-int RM_StringToLongLong(RedisModuleString *str, long long *ll) {
+int RM_StringToLongLong(const RedisModuleString *str, long long *ll) {
     return string2ll(str->ptr,sdslen(str->ptr),ll) ? REDISMODULE_OK :
                                                      REDISMODULE_ERR;
 }
 
 /* Convert the string into a double, storing it at `*d`.
  * Returns REDISMODULE_OK on success or REDISMODULE_ERR if the string is
  * not a valid string representation of a double value. */
-int RM_StringToDouble(RedisModuleString *str, double *d) {
+int RM_StringToDouble(const RedisModuleString *str, double *d) {
     int retval = getDoubleFromObject(str,d);
     return (retval == C_OK) ? REDISMODULE_OK : REDISMODULE_ERR;
 }
@@ -933,7 +1080,7 @@ void *RM_OpenKey(RedisModuleCtx *ctx, robj *keyname, int mode) {
     kp->value = value;
     kp->iter = NULL;
     kp->mode = mode;
-    RM_ZsetRangeStop(kp);
+    zsetKeyReset(kp);
     autoMemoryAdd(ctx,REDISMODULE_AM_KEY,kp);
     return (void*)kp;
 }
@@ -961,6 +1108,7 @@ int RM_KeyType(RedisModuleKey *key) {
     case OBJ_SET: return REDISMODULE_KEYTYPE_SET;
     case OBJ_ZSET: return REDISMODULE_KEYTYPE_ZSET;
     case OBJ_HASH: return REDISMODULE_KEYTYPE_HASH;
+    case OBJ_MODULE: return REDISMODULE_KEYTYPE_MODULE;
     default: return 0;
     }
 }
@@ -1318,6 +1466,12 @@ int RM_ZsetScore(RedisModuleKey *key, RedisModuleString *ele, double *score) {
  * Key API for Sorted Set iterator
  * -------------------------------------------------------------------------- */
 
+void zsetKeyReset(RedisModuleKey *key) {
+    key->ztype = REDISMODULE_ZSET_RANGE_NONE;
+    key->zcurrent = NULL;
+    key->zer = 1;
+}
+
 /* Stop a sorted set iteration. */
 void RM_ZsetRangeStop(RedisModuleKey *key) {
     /* Free resources if needed. */
@@ -1326,9 +1480,7 @@ void RM_ZsetRangeStop(RedisModuleKey *key) {
     /* Setup sensible values so that misused iteration API calls when an
      * iterator is not active will result into something more sensible
      * than crashing. */
-    key->ztype = REDISMODULE_ZSET_RANGE_NONE;
-    key->zcurrent = NULL;
-    key->zer = 1;
+    zsetKeyReset(key);
 }
 
 /* Return the "End of range" flag value to signal the end of the iteration. */
@@ -1705,17 +1857,20 @@ int RM_HashSet(RedisModuleKey *key, int flags, ...) {
             continue;
         }
 
+        int low_flags = HASH_SET_COPY;
         /* If CFIELDS is active, we can pass the ownership of the
          * SDS object to the low level function that sets the field
          * to avoid a useless copy. */
-        int low_flags = HASH_SET_COPY;
         if (flags & REDISMODULE_HASH_CFIELDS)
             low_flags |= HASH_SET_TAKE_FIELD;
         updated += hashTypeSet(key->value, field->ptr, value->ptr, low_flags);
-        field->ptr = NULL; /* Ownership is now of hashTypeSet() */
 
-        /* Cleanup */
-        if (flags & REDISMODULE_HASH_CFIELDS) decrRefCount(field);
+        /* If CFIELDS is active, SDS string ownership is now of hashTypeSet(),
+         * however we still have to release the 'field' object shell. */
+        if (flags & REDISMODULE_HASH_CFIELDS) {
+           field->ptr = NULL; /* Prevent the SDS string from being freed. */
+           decrRefCount(field);
+        }
     }
     va_end(ap);
     moduleDelKeyIfEmpty(key);
@@ -2195,6 +2350,490 @@ const char *RM_CallReplyProto(RedisModuleCallReply *reply, size_t *len) {
 }
 
 /* --------------------------------------------------------------------------
+ * Modules data types
+ *
+ * When String DMA or using existing data structures is not enough, it is
+ * possible to create new data types from scratch and export them to
+ * Redis. The module must provide a set of callbacks for handling the
+ * new values exported (for example in order to provide RDB saving/loading,
+ * AOF rewrite, and so forth). In this section we define this API.
+ * -------------------------------------------------------------------------- */
+
+/* Turn a 9 chars name in the specified charset and a 10 bit encver into
+ * a single 64 bit unsigned integer that represents this exact module name
+ * and version. This final number is called a "type ID" and is used when
+ * writing module exported values to RDB files, in order to re-associate the
+ * value to the right module to load them during RDB loading.
+ *
+ * If the string is not of the right length or the charset is wrong, or
+ * if encver is outside the unsigned 10 bit integer range, 0 is returned,
+ * otherwise the function returns the right type ID.
+ *
+ * The resulting 64 bit integer is composed as follows:
+ *
+ * (high order bits) 6|6|6|6|6|6|6|6|6|10 (low order bits)
+ *
+ * The first 6 bits value is the first character, name[0], while the last
+ * 6 bits value, immediately before the 10 bits integer, is name[8].
+ * The last 10 bits are the encoding version.
+ *
+ * Note that a name and encver combo of "AAAAAAAAA" and 0, will produce
+ * zero as return value, that is the same we use to signal errors, thus
+ * this combination is invalid, and also useless since type names should
+ * try to be vary to avoid collisions. */
+
+const char *ModuleTypeNameCharSet =
+             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
+             "abcdefghijklmnopqrstuvwxyz"
+             "0123456789-_";
+
+uint64_t moduleTypeEncodeId(const char *name, int encver) {
+    /* We use 64 symbols so that we can map each character into 6 bits
+     * of the final output. */
+    const char *cset = ModuleTypeNameCharSet;
+    if (strlen(name) != 9) return 0;
+    if (encver < 0 || encver > 1023) return 0;
+
+    uint64_t id = 0;
+    for (int j = 0; j < 9; j++) {
+        char *p = strchr(cset,name[j]);
+        if (!p) return 0;
+        unsigned long pos = p-cset;
+        id = (id << 6) | pos;
+    }
+    id = (id << 10) | encver;
+    return id;
+}
+
+/* Search, in the list of exported data types of all the modules registered,
+ * a type with the same name as the one given. Returns the moduleType
+ * structure pointer if such a module is found, or NULL otherwise. */
+moduleType *moduleTypeLookupModuleByName(const char *name) {
+    dictIterator *di = dictGetIterator(modules);
+    dictEntry *de;
+
+    while ((de = dictNext(di)) != NULL) {
+        struct RedisModule *module = dictGetVal(de);
+        listIter li;
+        listNode *ln;
+
+        listRewind(module->types,&li);
+        while((ln = listNext(&li))) {
+            moduleType *mt = ln->value;
+            if (memcmp(name,mt->name,sizeof(mt->name)) == 0) {
+                dictReleaseIterator(di);
+                return mt;
+            }
+        }
+    }
+    dictReleaseIterator(di);
+    return NULL;
+}
+
+/* Lookup a module by ID, with caching. This function is used during RDB
+ * loading. Modules exporting data types should never be able to unload, so
+ * our cache does not need to expire. */
+#define MODULE_LOOKUP_CACHE_SIZE 3
+
+moduleType *moduleTypeLookupModuleByID(uint64_t id) {
+    static struct {
+        uint64_t id;
+        moduleType *mt;
+    } cache[MODULE_LOOKUP_CACHE_SIZE];
+
+    /* Search in cache to start. */
+    int j;
+    for (j = 0; j < MODULE_LOOKUP_CACHE_SIZE; j++)
+        if (cache[j].id == id) return cache[j].mt;
+
+    /* Slow module by module lookup. */
+    moduleType *mt = NULL;
+    dictIterator *di = dictGetIterator(modules);
+    dictEntry *de;
+
+    while ((de = dictNext(di)) != NULL) {
+        struct RedisModule *module = dictGetVal(de);
+        listIter li;
+        listNode *ln;
+
+        listRewind(module->types,&li);
+        while((ln = listNext(&li))) {
+            mt = ln->value;
+            /* Compare only the 54 bit module identifier and not the
+             * encoding version. */
+            if (mt->id >> 10 == id >> 10) break;
+        }
+    }
+    dictReleaseIterator(di);
+
+    /* Add to cache if possible. */
+    if (mt && j < MODULE_LOOKUP_CACHE_SIZE) {
+        cache[j].id = id;
+        cache[j].mt = mt;
+    }
+    return mt;
+}
+
+/* Turn an (unresolved) module ID into a type name, to show the user an
+ * error when RDB files contain module data we can't load. */
+void moduleTypeNameByID(char *name, uint64_t moduleid) {
+    const char *cset = ModuleTypeNameCharSet;
+
+    name[0] = '\0';
+    char *p = name+8;
+    moduleid >>= 10;
+    for (int j = 0; j < 9; j++) {
+        *p-- = cset[moduleid & 63];
+        moduleid >>= 6;
+    }
+}
+
+/* Register a new data type exported by the module. The parameters are the
+ * following. Please for in depth documentation check the modules API
+ * documentation, especially the INTRO.md file.
+ *
+ * * **name**: A 9 characters data type name that MUST be unique in the Redis
+ *   Modules ecosystem. Be creative... and there will be no collisions. Use
+ *   the charset A-Z a-z 9-0, plus the two "-_" characters. A good
+ *   idea is to use, for example `<typename>-<vendor>`. For example
+ *   "tree-AntZ" may mean "Tree data structure by @antirez". To use both
+ *   lower case and upper case letters helps in order to prevent collisions.
+ * * **encver**: Encoding version, which is, the version of the serialization
+ *   that a module used in order to persist data. As long as the "name"
+ *   matches, the RDB loading will be dispatched to the type callbacks
+ *   whatever 'encver' is used, however the module can understand if
+ *   the encoding it must load are of an older version of the module.
+ *   For example the module "tree-AntZ" initially used encver=0. Later
+ *   after an upgrade, it started to serialize data in a different format
+ *   and to register the type with encver=1. However this module may
+ *   still load old data produced by an older version if the rdb_load
+ *   callback is able to check the encver value and act accordingly.
+ *   The encver must be a positive value between 0 and 1023.
+ * * **rdb_load**: A callback function pointer that loads data from RDB files.
+ * * **rdb_save**: A callback function pointer that saves data to RDB files.
+ * * **aof_rewrite**: A callback function pointer that rewrites data as commands.
+ * * **digest**: A callback function pointer that is used for `DEBUG DIGEST`.
+ * * **free**: A callback function pointer that can free a type value.
+ *
+ * Note: the module name "AAAAAAAAA" is reserved and produces an error, it
+ * happens to be pretty lame as well.
+ *
+ * If there is already a module registering a type with the same name,
+ * and if the module name or encver is invalid, NULL is returned.
+ * Otherwise the new type is registered into Redis, and a reference of
+ * type RedisModuleType is returned: the caller of the function should store
+ * this reference into a gobal variable to make future use of it in the
+ * modules type API, since a single module may register multiple types.
+ * Example code fragment:
+ *
+ *      static RedisModuleType *BalancedTreeType;
+ *
+ *      int RedisModule_OnLoad(RedisModuleCtx *ctx) {
+ *          // some code here ...
+ *          BalancedTreeType = RM_CreateDataType(...);
+ *      }
+ */
+moduleType *RM_CreateDataType(RedisModuleCtx *ctx, const char *name, int encver, moduleTypeLoadFunc rdb_load, moduleTypeSaveFunc rdb_save, moduleTypeRewriteFunc aof_rewrite, moduleTypeDigestFunc digest, moduleTypeFreeFunc free) {
+    uint64_t id = moduleTypeEncodeId(name,encver);
+    if (id == 0) return NULL;
+    if (moduleTypeLookupModuleByName(name) != NULL) return NULL;
+
+    moduleType *mt = zmalloc(sizeof(*mt));
+    mt->id = id;
+    mt->module = ctx->module;
+    mt->rdb_load = rdb_load;
+    mt->rdb_save = rdb_save;
+    mt->aof_rewrite = aof_rewrite;
+    mt->digest = digest;
+    mt->free = free;
+    memcpy(mt->name,name,sizeof(mt->name));
+    listAddNodeTail(ctx->module->types,mt);
+    return mt;
+}
+
+/* If the key is open for writing, set the specified module type object
+ * as the value of the key, deleting the old value if any.
+ * On success REDISMODULE_OK is returned. If the key is not open for
+ * writing or there is an active iterator, REDISMODULE_ERR is returned. */
+int RM_ModuleTypeSetValue(RedisModuleKey *key, moduleType *mt, void *value) {
+    if (!(key->mode & REDISMODULE_WRITE) || key->iter) return REDISMODULE_ERR;
+    RM_DeleteKey(key);
+    robj *o = createModuleObject(mt,value);
+    setKey(key->db,key->key,o);
+    decrRefCount(o);
+    key->value = o;
+    return REDISMODULE_OK;
+}
+
+/* Assuming RedisModule_KeyType() returned REDISMODULE_KEYTYPE_MODULE on
+ * the key, returns the moduel type pointer of the value stored at key.
+ *
+ * If the key is NULL, is not associated with a module type, or is empty,
+ * then NULL is returned instead. */
+moduleType *RM_ModuleTypeGetType(RedisModuleKey *key) {
+    if (key == NULL ||
+        key->value == NULL ||
+        RM_KeyType(key) != REDISMODULE_KEYTYPE_MODULE) return NULL;
+    moduleValue *mv = key->value->ptr;
+    return mv->type;
+}
+
+/* Assuming RedisModule_KeyType() returned REDISMODULE_KEYTYPE_MODULE on
+ * the key, returns the module type low-level value stored at key, as
+ * it was set by the user via RedisModule_ModuleTypeSet().
+ *
+ * If the key is NULL, is not associated with a module type, or is empty,
+ * then NULL is returned instead. */
+void *RM_ModuleTypeGetValue(RedisModuleKey *key) {
+    if (key == NULL ||
+        key->value == NULL ||
+        RM_KeyType(key) != REDISMODULE_KEYTYPE_MODULE) return NULL;
+    moduleValue *mv = key->value->ptr;
+    return mv->value;
+}
+
+/* --------------------------------------------------------------------------
+ * RDB loading and saving functions
+ * -------------------------------------------------------------------------- */
+
+/* Called when there is a load error in the context of a module. This cannot
+ * be recovered like for the built-in types. */
+void moduleRDBLoadError(RedisModuleIO *io) {
+    serverLog(LL_WARNING,
+        "Error loading data from RDB (short read or EOF). "
+        "Read performed by module '%s' about type '%s' "
+        "after reading '%llu' bytes of a value.",
+        io->type->module->name,
+        io->type->name,
+        (unsigned long long)io->bytes);
+    exit(1);
+}
+
+/* Save an unsigned 64 bit value into the RDB file. This function should only
+ * be called in the context of the rdb_save method of modules implementing new
+ * data types. */
+void RM_SaveUnsigned(RedisModuleIO *io, uint64_t value) {
+    if (io->error) return;
+    int retval = rdbSaveLen(io->rio, value);
+    if (retval == -1) {
+        io->error = 1;
+    } else {
+        io->bytes += retval;
+    }
+}
+
+/* Load an unsigned 64 bit value from the RDB file. This function should only
+ * be called in the context of the rdb_load method of modules implementing
+ * new data types. */
+uint64_t RM_LoadUnsigned(RedisModuleIO *io) {
+    uint64_t value;
+    int retval = rdbLoadLenByRef(io->rio, NULL, &value);
+    if (retval == -1) {
+        moduleRDBLoadError(io);
+        return 0; /* Never reached. */
+    }
+    return value;
+}
+
+/* Like RedisModule_SaveUnsigned() but for signed 64 bit values. */
+void RM_SaveSigned(RedisModuleIO *io, int64_t value) {
+    union {uint64_t u; int64_t i;} conv;
+    conv.i = value;
+    RM_SaveUnsigned(io,conv.u);
+}
+
+/* Like RedisModule_LoadUnsigned() but for signed 64 bit values. */
+int64_t RM_LoadSigned(RedisModuleIO *io) {
+    union {uint64_t u; int64_t i;} conv;
+    conv.u = RM_LoadUnsigned(io);
+    return conv.i;
+}
+
+/* In the context of the rdb_save method of a module type, saves a
+ * string into the RDB file taking as input a RedisModuleString.
+ *
+ * The string can be later loaded with RedisModule_LoadString() or
+ * other Load family functions expecting a serialized string inside
+ * the RDB file. */
+void RM_SaveString(RedisModuleIO *io, RedisModuleString *s) {
+    if (io->error) return;
+    int retval = rdbSaveStringObject(io->rio,s);
+    if (retval == -1) {
+        io->error = 1;
+    } else {
+        io->bytes += retval;
+    }
+}
+
+/* Like RedisModule_SaveString() but takes a raw C pointer and length
+ * as input. */
+void RM_SaveStringBuffer(RedisModuleIO *io, const char *str, size_t len) {
+    if (io->error) return;
+    int retval = rdbSaveRawString(io->rio,(unsigned char*)str,len);
+    if (retval == -1) {
+        io->error = 1;
+    } else {
+        io->bytes += retval;
+    }
+}
+
+/* Implements RM_LoadString() and RM_LoadStringBuffer() */
+void *moduleLoadString(RedisModuleIO *io, int plain, size_t *lenptr) {
+    void *s = rdbGenericLoadStringObject(io->rio,
+              plain ? RDB_LOAD_PLAIN : RDB_LOAD_NONE, lenptr);
+    if (s == NULL) {
+        moduleRDBLoadError(io);
+        return NULL; /* Never reached. */
+    }
+    return s;
+}
+
+/* In the context of the rdb_load method of a module data type, loads a string
+ * from the RDB file, that was previously saved with RedisModule_SaveString()
+ * functions family.
+ *
+ * The returned string is a newly allocated RedisModuleString object, and
+ * the user should at some point free it with a call to RedisModule_FreeString().
+ *
+ * If the data structure does not store strings as RedisModuleString objects,
+ * the similar function RedisModule_LoadStringBuffer() could be used instead. */
+RedisModuleString *RM_LoadString(RedisModuleIO *io) {
+    return moduleLoadString(io,0,NULL);
+}
+
+/* Like RedisModule_LoadString() but returns an heap allocated string that
+ * was allocated with RedisModule_Alloc(), and can be resized or freed with
+ * RedisModule_Realloc() or RedisModule_Free().
+ *
+ * The size of the string is stored at '*lenptr' if not NULL.
+ * The returned string is not automatically NULL termianted, it is loaded
+ * exactly as it was stored inisde the RDB file. */
+char *RM_LoadStringBuffer(RedisModuleIO *io, size_t *lenptr) {
+    return moduleLoadString(io,1,lenptr);
+}
+
+/* In the context of the rdb_save method of a module data type, saves a double
+ * value to the RDB file. The double can be a valid number, a NaN or infinity.
+ * It is possible to load back the value with RedisModule_LoadDouble(). */
+void RM_SaveDouble(RedisModuleIO *io, double value) {
+    if (io->error) return;
+    int retval = rdbSaveBinaryDoubleValue(io->rio, value);
+    if (retval == -1) {
+        io->error = 1;
+    } else {
+        io->bytes += retval;
+    }
+}
+
+/* In the context of the rdb_save method of a module data type, loads back the
+ * double value saved by RedisModule_SaveDouble(). */
+double RM_LoadDouble(RedisModuleIO *io) {
+    double value;
+    int retval = rdbLoadBinaryDoubleValue(io->rio, &value);
+    if (retval == -1) {
+        moduleRDBLoadError(io);
+        return 0; /* Never reached. */
+    }
+    return value;
+}
+
+/* --------------------------------------------------------------------------
+ * AOF API for modules data types
+ * -------------------------------------------------------------------------- */
+
+/* Emits a command into the AOF during the AOF rewriting process. This function
+ * is only called in the context of the aof_rewrite method of data types exported
+ * by a module. The command works exactly like RedisModule_Call() in the way
+ * the parameters are passed, but it does not return anything as the error
+ * handling is performed by Redis itself. */
+void RM_EmitAOF(RedisModuleIO *io, const char *cmdname, const char *fmt, ...) {
+    if (io->error) return;
+    struct redisCommand *cmd;
+    robj **argv = NULL;
+    int argc = 0, flags = 0, j;
+    va_list ap;
+
+    cmd = lookupCommandByCString((char*)cmdname);
+    if (!cmd) {
+        serverLog(LL_WARNING,
+            "Fatal: AOF method for module data type '%s' tried to "
+            "emit unknown command '%s'",
+            io->type->name, cmdname);
+        io->error = 1;
+        errno = EINVAL;
+        return;
+    }
+
+    /* Emit the arguments into the AOF in Redis protocol format. */
+    va_start(ap, fmt);
+    argv = moduleCreateArgvFromUserFormat(cmdname,fmt,&argc,&flags,ap);
+    va_end(ap);
+    if (argv == NULL) {
+        serverLog(LL_WARNING,
+            "Fatal: AOF method for module data type '%s' tried to "
+            "call RedisModule_EmitAOF() with wrong format specifiers '%s'",
+            io->type->name, fmt);
+        io->error = 1;
+        errno = EINVAL;
+        return;
+    }
+
+    /* Bulk count. */
+    if (!io->error && rioWriteBulkCount(io->rio,'*',argc) == 0)
+        io->error = 1;
+
+    /* Arguments. */
+    for (j = 0; j < argc; j++) {
+        if (!io->error && rioWriteBulkObject(io->rio,argv[j]) == 0)
+            io->error = 1;
+        decrRefCount(argv[j]);
+    }
+    zfree(argv);
+    return;
+}
+
+/* --------------------------------------------------------------------------
+ * Logging
+ * -------------------------------------------------------------------------- */
+
+/* Produces a log message to the standard Redis log, the format accepts
+ * printf-alike specifiers, while level is a string describing the log
+ * level to use when emitting the log, and must be one of the following:
+ *
+ * * "debug"
+ * * "verbose"
+ * * "notice"
+ * * "warning"
+ *
+ * If the specified log level is invalid, verbose is used by default.
+ * There is a fixed limit to the length of the log line this function is able
+ * to emit, this limti is not specified but is guaranteed to be more than
+ * a few lines of text.
+ */
+void RM_Log(RedisModuleCtx *ctx, const char *levelstr, const char *fmt, ...) {
+    va_list ap;
+    char msg[LOG_MAX_LEN];
+    size_t name_len;
+    int level;
+
+    if (!ctx->module) return;   /* Can only log if module is initialized */
+
+    if (!strcasecmp(levelstr,"debug")) level = LL_DEBUG;
+    else if (!strcasecmp(levelstr,"verbose")) level = LL_VERBOSE;
+    else if (!strcasecmp(levelstr,"notice")) level = LL_NOTICE;
+    else if (!strcasecmp(levelstr,"warning")) level = LL_WARNING;
+    else level = LL_VERBOSE; /* Default. */
+
+    name_len = snprintf(msg, sizeof(msg),"<%s> ", ctx->module->name);
+
+    va_start(ap, fmt);
+    vsnprintf(msg + name_len, sizeof(msg) - name_len, fmt, ap);
+    va_end(ap);
+
+    serverLogRaw(level,msg);
+}
+
+/* --------------------------------------------------------------------------
  * Modules API internals
  * -------------------------------------------------------------------------- */
 
@@ -2229,6 +2868,11 @@ int moduleRegisterApi(const char *funcname, void *funcptr) {
 /* Register all the APIs we export. */
 void moduleRegisterCoreAPI(void) {
     server.moduleapi = dictCreate(&moduleAPIDictType,NULL);
+    REGISTER_API(Alloc);
+    REGISTER_API(Calloc);
+    REGISTER_API(Realloc);
+    REGISTER_API(Free);
+    REGISTER_API(Strdup);
     REGISTER_API(CreateCommand);
     REGISTER_API(SetModuleAttribs);
     REGISTER_API(WrongArity);
@@ -2263,6 +2907,7 @@ void moduleRegisterCoreAPI(void) {
     REGISTER_API(CreateStringFromCallReply);
     REGISTER_API(CreateString);
     REGISTER_API(CreateStringFromLongLong);
+    REGISTER_API(CreateStringFromString);
     REGISTER_API(FreeString);
     REGISTER_API(StringPtrLen);
     REGISTER_API(AutoMemory);
@@ -2292,6 +2937,23 @@ void moduleRegisterCoreAPI(void) {
     REGISTER_API(IsKeysPositionRequest);
     REGISTER_API(KeyAtPos);
     REGISTER_API(GetClientId);
+    REGISTER_API(PoolAlloc);
+    REGISTER_API(CreateDataType);
+    REGISTER_API(ModuleTypeSetValue);
+    REGISTER_API(ModuleTypeGetType);
+    REGISTER_API(ModuleTypeGetValue);
+    REGISTER_API(SaveUnsigned);
+    REGISTER_API(LoadUnsigned);
+    REGISTER_API(SaveSigned);
+    REGISTER_API(LoadSigned);
+    REGISTER_API(SaveString);
+    REGISTER_API(SaveStringBuffer);
+    REGISTER_API(LoadString);
+    REGISTER_API(LoadStringBuffer);
+    REGISTER_API(SaveDouble);
+    REGISTER_API(LoadDouble);
+    REGISTER_API(EmitAOF);
+    REGISTER_API(Log);
 }
 
 /* Global initialization at Redis startup. */
@@ -2316,25 +2978,28 @@ void moduleLoadFromQueue(void) {
 
     listRewind(server.loadmodule_queue,&li);
     while((ln = listNext(&li))) {
-        sds modulepath = ln->value;
-        if (moduleLoad(modulepath) == C_ERR) {
+        struct moduleLoadQueueEntry *loadmod = ln->value;
+        if (moduleLoad(loadmod->path,(void **)loadmod->argv,loadmod->argc)
+            == C_ERR)
+        {
             serverLog(LL_WARNING,
                 "Can't load module from %s: server aborting",
-                modulepath);
+                loadmod->path);
             exit(1);
         }
     }
 }
 
 void moduleFreeModuleStructure(struct RedisModule *module) {
+    listRelease(module->types);
     sdsfree(module->name);
     zfree(module);
 }
 
 /* Load a module and initialize it. On success C_OK is returned, otherwise
  * C_ERR is returned. */
-int moduleLoad(const char *path) {
-    int (*onload)(void *);
+int moduleLoad(const char *path, void **module_argv, int module_argc) {
+    int (*onload)(void *, void **, int);
     void *handle;
     RedisModuleCtx ctx = REDISMODULE_CTX_INIT;
 
@@ -2343,14 +3008,14 @@ int moduleLoad(const char *path) {
         serverLog(LL_WARNING, "Module %s failed to load: %s", path, dlerror());
         return C_ERR;
     }
-    onload = (int (*)(void *))(unsigned long) dlsym(handle,"RedisModule_OnLoad");
+    onload = (int (*)(void *, void **, int))(unsigned long) dlsym(handle,"RedisModule_OnLoad");
     if (onload == NULL) {
         serverLog(LL_WARNING,
             "Module %s does not export RedisModule_OnLoad() "
             "symbol. Module not loaded.",path);
         return C_ERR;
     }
-    if (onload((void*)&ctx) == REDISMODULE_ERR) {
+    if (onload((void*)&ctx,module_argv,module_argc) == REDISMODULE_ERR) {
         if (ctx.module) moduleFreeModuleStructure(ctx.module);
         dlclose(handle);
         serverLog(LL_WARNING,
@@ -2362,21 +3027,29 @@ int moduleLoad(const char *path) {
     dictAdd(modules,ctx.module->name,ctx.module);
     ctx.module->handle = handle;
     serverLog(LL_NOTICE,"Module '%s' loaded from %s",ctx.module->name,path);
+    moduleFreeContext(&ctx);
     return C_OK;
 }
 
 /* Unload the module registered with the specified name. On success
  * C_OK is returned, otherwise C_ERR is returned and errno is set
  * to the following values depending on the type of error:
  *
- * ENONET: No such module having the specified name. */
+ * ENONET: No such module having the specified name.
+ * EBUSY: The module exports a new data type and can only be reloaded. */
 int moduleUnload(sds name) {
     struct RedisModule *module = dictFetchValue(modules,name);
+
     if (module == NULL) {
         errno = ENOENT;
         return REDISMODULE_ERR;
     }
 
+    if (listLength(module->types)) {
+        errno = EBUSY;
+        return REDISMODULE_ERR;
+    }
+
     /* Unregister all the commands registered by this module. */
     dictIterator *di = dictGetSafeIterator(server.commands);
     dictEntry *de;
@@ -2410,21 +3083,27 @@ int moduleUnload(sds name) {
     /* Remove from list of modules. */
     serverLog(LL_NOTICE,"Module %s unloaded",module->name);
     dictDelete(modules,module->name);
-
-    /* Free the module structure. */
-    zfree(module);
+    moduleFreeModuleStructure(module);
 
     return REDISMODULE_OK;
 }
 
 /* Redis MODULE command.
  *
- * MODULE LOAD <path> */
+ * MODULE LOAD <path> [args...] */
 void moduleCommand(client *c) {
     char *subcmd = c->argv[1]->ptr;
 
-    if (!strcasecmp(subcmd,"load") && c->argc == 3) {
-        if (moduleLoad(c->argv[2]->ptr) == C_OK)
+    if (!strcasecmp(subcmd,"load") && c->argc >= 3) {
+        robj **argv = NULL;
+        int argc = 0;
+
+        if (c->argc > 3) {
+            argc = c->argc - 3;
+            argv = &c->argv[3];
+        }
+
+        if (moduleLoad(c->argv[2]->ptr,(void **)argv,argc) == C_OK)
             addReply(c,shared.ok);
         else
             addReplyError(c,
@@ -2433,9 +3112,17 @@ void moduleCommand(client *c) {
         if (moduleUnload(c->argv[2]->ptr) == C_OK)
             addReply(c,shared.ok);
         else {
-            char *errmsg = "operation not possible.";
+            char *errmsg;
             switch(errno) {
-            case ENOENT: errmsg = "no such module with that name";
+            case ENOENT:
+                errmsg = "no such module with that name";
+                break;
+            case EBUSY:
+                errmsg = "the module exports one or more module-side data types, can't unload";
+                break;
+            default:
+                errmsg = "operation not possible.";
+                break;
             }
             addReplyErrorFormat(c,"Error unloading module: %s",errmsg);
         }