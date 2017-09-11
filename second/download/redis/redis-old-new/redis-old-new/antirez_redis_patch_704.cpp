@@ -7,14 +7,37 @@
 #include "lua.h"
 #include "lauxlib.h"
 
-#define LUACMSGPACK_VERSION     "lua-cmsgpack 0.3.0"
+#define LUACMSGPACK_NAME        "cmsgpack"
+#define LUACMSGPACK_SAFE_NAME   "cmsgpack_safe"
+#define LUACMSGPACK_VERSION     "lua-cmsgpack 0.4.0"
 #define LUACMSGPACK_COPYRIGHT   "Copyright (C) 2012, Salvatore Sanfilippo"
 #define LUACMSGPACK_DESCRIPTION "MessagePack C implementation for Lua"
 
 #define LUACMSGPACK_MAX_NESTING  16 /* Max tables nesting. */
 
-/* ==============================================================================
- * MessagePack implementation and bindings for Lua 5.1.
+/* Allows a preprocessor directive to override MAX_NESTING */
+#ifndef LUACMSGPACK_MAX_NESTING
+    #define LUACMSGPACK_MAX_NESTING  16
+#endif
+
+#if (_XOPEN_SOURCE >= 600 || _ISOC99_SOURCE || _POSIX_C_SOURCE >= 200112L)
+    #define IS_FINITE(x) isfinite(x)
+#else
+    #define IS_FINITE(x) ((x) == (x) && (x) + 1 > (x))
+#endif
+
+/* Check if float or double can be an integer without loss of precision */
+#define IS_INT_TYPE_EQUIVALENT(x, T) (IS_FINITE(x) && (T)(x) == (x))
+
+#define IS_INT64_EQUIVALENT(x) IS_INT_TYPE_EQUIVALENT(x, int64_t)
+#define IS_INT_EQUIVALENT(x) IS_INT_TYPE_EQUIVALENT(x, int)
+
+#if LUA_VERSION_NUM < 503
+    #define lua_pushunsigned(L, n) lua_pushinteger(L, n)
+#endif
+
+/* =============================================================================
+ * MessagePack implementation and bindings for Lua 5.1/5.2.
  * Copyright(C) 2012 Salvatore Sanfilippo <antirez@gmail.com>
  *
  * http://github.com/antirez/lua-cmsgpack
@@ -29,19 +52,23 @@
  * 20-Feb-2012 (ver 0.2.0): Tables encoding improved.
  * 20-Feb-2012 (ver 0.2.1): Minor bug fixing.
  * 20-Feb-2012 (ver 0.3.0): Module renamed lua-cmsgpack (was lua-msgpack).
- * ============================================================================ */
+ * 04-Apr-2014 (ver 0.3.1): Lua 5.2 support and minor bug fix.
+ * 07-Apr-2014 (ver 0.4.0): Multiple pack/unpack, lua allocator, efficiency.
+ * ========================================================================== */
 
-/* --------------------------- Endian conversion --------------------------------
- * We use it only for floats and doubles, all the other conversions are performed
+/* -------------------------- Endian conversion --------------------------------
+ * We use it only for floats and doubles, all the other conversions performed
  * in an endian independent fashion. So the only thing we need is a function
- * that swaps a binary string if the arch is little endian (and left it untouched
+ * that swaps a binary string if arch is little endian (and left it untouched
  * otherwise). */
 
 /* Reverse memory bytes if arch is little endian. Given the conceptual
- * simplicity of the Lua build system we prefer to check for endianess at runtime.
+ * simplicity of the Lua build system we prefer check for endianess at runtime.
  * The performance difference should be acceptable. */
 static void memrevifle(void *ptr, size_t len) {
-    unsigned char *p = ptr, *e = p+len-1, aux;
+    unsigned char   *p = (unsigned char *)ptr,
+                    *e = (unsigned char *)p+len-1,
+                    aux;
     int test = 1;
     unsigned char *testp = (unsigned char*) &test;
 
@@ -56,30 +83,44 @@ static void memrevifle(void *ptr, size_t len) {
     }
 }
 
-/* ----------------------------- String buffer ----------------------------------
+/* ---------------------------- String buffer ----------------------------------
  * This is a simple implementation of string buffers. The only opereation
  * supported is creating empty buffers and appending bytes to it.
  * The string buffer uses 2x preallocation on every realloc for O(N) append
  * behavior.  */
 
 typedef struct mp_buf {
+    lua_State *L;
     unsigned char *b;
     size_t len, free;
 } mp_buf;
 
-static mp_buf *mp_buf_new(void) {
-    mp_buf *buf = malloc(sizeof(*buf));
-    
+static void *mp_realloc(lua_State *L, void *target, size_t osize,size_t nsize) {
+    void *(*local_realloc) (void *, void *, size_t osize, size_t nsize) = NULL;
+    void *ud;
+
+    local_realloc = lua_getallocf(L, &ud);
+
+    return local_realloc(ud, target, osize, nsize);
+}
+
+static mp_buf *mp_buf_new(lua_State *L) {
+    mp_buf *buf = NULL;
+
+    /* Old size = 0; new size = sizeof(*buf) */
+    buf = (mp_buf*)mp_realloc(L, buf, 0, sizeof(*buf));
+
+    buf->L = L;
     buf->b = NULL;
     buf->len = buf->free = 0;
     return buf;
 }
 
-void mp_buf_append(mp_buf *buf, const unsigned char *s, size_t len) {
+static void mp_buf_append(mp_buf *buf, const unsigned char *s, size_t len) {
     if (buf->free < len) {
         size_t newlen = buf->len+len;
 
-        buf->b = realloc(buf->b,newlen*2);
+        buf->b = (unsigned char*)mp_realloc(buf->L, buf->b, buf->len, newlen*2);
         buf->free = newlen;
     }
     memcpy(buf->b+buf->len,s,len);
@@ -88,11 +129,11 @@ void mp_buf_append(mp_buf *buf, const unsigned char *s, size_t len) {
 }
 
 void mp_buf_free(mp_buf *buf) {
-    free(buf->b);
-    free(buf);
+    mp_realloc(buf->L, buf->b, buf->len, 0); /* realloc to 0 = free */
+    mp_realloc(buf->L, buf, sizeof(*buf), 0);
 }
 
-/* ------------------------------ String cursor ----------------------------------
+/* ---------------------------- String cursor ----------------------------------
  * This simple data structure is used for parsing. Basically you create a cursor
  * using a string pointer and a length, then it is possible to access the
  * current string position with cursor->p, check the remaining length
@@ -102,7 +143,7 @@ void mp_buf_free(mp_buf *buf) {
  * be used to report errors. */
 
 #define MP_CUR_ERROR_NONE   0
-#define MP_CUR_ERROR_EOF    1   /* Not enough data to complete the opereation. */
+#define MP_CUR_ERROR_EOF    1   /* Not enough data to complete opereation. */
 #define MP_CUR_ERROR_BADFMT 2   /* Bad data format */
 
 typedef struct mp_cur {
@@ -111,17 +152,10 @@ typedef struct mp_cur {
     int err;
 } mp_cur;
 
-static mp_cur *mp_cur_new(const unsigned char *s, size_t len) {
-    mp_cur *cursor = malloc(sizeof(*cursor));
-
+static void mp_cur_init(mp_cur *cursor, const unsigned char *s, size_t len) {
     cursor->p = s;
     cursor->left = len;
     cursor->err = MP_CUR_ERROR_NONE;
-    return cursor;
-}
-
-static void mp_cur_free(mp_cur *cursor) {
-    free(cursor);
 }
 
 #define mp_cur_consume(_c,_len) do { _c->p += _len; _c->left -= _len; } while(0)
@@ -136,7 +170,7 @@ static void mp_cur_free(mp_cur *cursor) {
     } \
 } while(0)
 
-/* --------------------------- Low level MP encoding -------------------------- */
+/* ------------------------- Low level MP encoding -------------------------- */
 
 static void mp_encode_bytes(mp_buf *buf, const unsigned char *s, size_t len) {
     unsigned char hdr[5];
@@ -299,7 +333,7 @@ static void mp_encode_map(mp_buf *buf, int64_t n) {
     mp_buf_append(buf,b,enclen);
 }
 
-/* ----------------------------- Lua types encoding --------------------------- */
+/* --------------------------- Lua types encoding --------------------------- */
 
 static void mp_encode_lua_string(lua_State *L, mp_buf *buf) {
     size_t len;
@@ -314,21 +348,34 @@ static void mp_encode_lua_bool(lua_State *L, mp_buf *buf) {
     mp_buf_append(buf,&b,1);
 }
 
+/* Lua 5.3 has a built in 64-bit integer type */
+static void mp_encode_lua_integer(lua_State *L, mp_buf *buf) {
+    lua_Integer i = lua_tointeger(L,-1);
+    mp_encode_int(buf, (int64_t)i);
+}
+
+/* Lua 5.2 and lower only has 64-bit doubles, so we need to
+ * detect if the double may be representable as an int
+ * for Lua < 5.3 */
 static void mp_encode_lua_number(lua_State *L, mp_buf *buf) {
     lua_Number n = lua_tonumber(L,-1);
 
-    if (floor(n) != n) {
-        mp_encode_double(buf,(double)n);
+    if (IS_INT64_EQUIVALENT(n)) {
+        mp_encode_lua_integer(L, buf);
     } else {
-        mp_encode_int(buf,(int64_t)n);
+        mp_encode_double(buf,(double)n);
     }
 }
 
 static void mp_encode_lua_type(lua_State *L, mp_buf *buf, int level);
 
 /* Convert a lua table into a message pack list. */
 static void mp_encode_lua_table_as_array(lua_State *L, mp_buf *buf, int level) {
+#if LUA_VERSION_NUM < 502
     size_t len = lua_objlen(L,-1), j;
+#else
+    size_t len = lua_rawlen(L,-1), j;
+#endif
 
     mp_encode_array(buf,len);
     for (j = 1; j <= len; j++) {
@@ -367,30 +414,42 @@ static void mp_encode_lua_table_as_map(lua_State *L, mp_buf *buf, int level) {
  * of keys from numerical keys from 1 up to N, with N being the total number
  * of elements, without any hole in the middle. */
 static int table_is_an_array(lua_State *L) {
-    long count = 0, max = 0, idx = 0;
+    int count = 0, max = 0;
+#if LUA_VERSION_NUM < 503
     lua_Number n;
+#else
+    lua_Integer n;
+#endif
+
+    /* Stack top on function entry */
+    int stacktop;
+
+    stacktop = lua_gettop(L);
 
     lua_pushnil(L);
     while(lua_next(L,-2)) {
         /* Stack: ... key value */
         lua_pop(L,1); /* Stack: ... key */
-        if (lua_type(L,-1) != LUA_TNUMBER) goto not_array;
-        n = lua_tonumber(L,-1);
-        idx = n;
-        if (idx != n || idx < 1) goto not_array;
+        /* The <= 0 check is valid here because we're comparing indexes. */
+#if LUA_VERSION_NUM < 503
+        if (!lua_isnumber(L,-1) || (n = lua_tonumber(L, -1)) <= 0 ||
+            !IS_INT_EQUIVALENT(n)) {
+#else
+        if (!lua_isinteger(L,-1) || (n = lua_tointeger(L, -1)) <= 0) {
+#endif
+            lua_settop(L, stacktop);
+            return 0;
+        }
+        max = (n > max ? n : max);
         count++;
-        max = idx;
     }
     /* We have the total number of elements in "count". Also we have
-     * the max index encountered in "idx". We can't reach this code
+     * the max index encountered in "max". We can't reach this code
      * if there are indexes <= 0. If you also note that there can not be
-     * repeated keys into a table, you have that if idx==count you are sure
+     * repeated keys into a table, you have that if max==count you are sure
      * that there are all the keys form 1 to count (both included). */
-    return idx == count;
-
-not_array:
-    lua_pop(L,1);
-    return 0;
+    lua_settop(L, stacktop);
+    return max == count;
 }
 
 /* If the length operator returns non-zero, that is, there is at least
@@ -405,6 +464,7 @@ static void mp_encode_lua_table(lua_State *L, mp_buf *buf, int level) {
 
 static void mp_encode_lua_null(lua_State *L, mp_buf *buf) {
     unsigned char b[1];
+    (void)L;
 
     b[0] = 0xc0;
     mp_buf_append(buf,b,1);
@@ -419,23 +479,59 @@ static void mp_encode_lua_type(lua_State *L, mp_buf *buf, int level) {
     switch(t) {
     case LUA_TSTRING: mp_encode_lua_string(L,buf); break;
     case LUA_TBOOLEAN: mp_encode_lua_bool(L,buf); break;
-    case LUA_TNUMBER: mp_encode_lua_number(L,buf); break;
+    case LUA_TNUMBER:
+    #if LUA_VERSION_NUM < 503
+        mp_encode_lua_number(L,buf); break;
+    #else
+        if (lua_isinteger(L, -1)) {
+            mp_encode_lua_integer(L, buf);
+        } else {
+            mp_encode_lua_number(L, buf);
+        }
+        break;
+    #endif
     case LUA_TTABLE: mp_encode_lua_table(L,buf,level); break;
     default: mp_encode_lua_null(L,buf); break;
     }
     lua_pop(L,1);
 }
 
+/*
+ * Packs all arguments as a stream for multiple upacking later.
+ * Returns error if no arguments provided.
+ */
 static int mp_pack(lua_State *L) {
-    mp_buf *buf = mp_buf_new();
+    int nargs = lua_gettop(L);
+    int i;
+    mp_buf *buf;
+
+    if (nargs == 0)
+        return luaL_argerror(L, 0, "MessagePack pack needs input.");
+
+    buf = mp_buf_new(L);
+    for(i = 1; i <= nargs; i++) {
+        /* Copy argument i to top of stack for _encode processing;
+         * the encode function pops it from the stack when complete. */
+        lua_pushvalue(L, i);
+
+        mp_encode_lua_type(L,buf,0);
 
-    mp_encode_lua_type(L,buf,0);
-    lua_pushlstring(L,(char*)buf->b,buf->len);
+        lua_pushlstring(L,(char*)buf->b,buf->len);
+
+        /* Reuse the buffer for the next operation by
+         * setting its free count to the total buffer size
+         * and the current position to zero. */
+        buf->free += buf->len;
+        buf->len = 0;
+    }
     mp_buf_free(buf);
+
+    /* Concatenate all nargs buffers together */
+    lua_concat(L, nargs);
     return 1;
 }
 
-/* --------------------------------- Decoding --------------------------------- */
+/* ------------------------------- Decoding --------------------------------- */
 
 void mp_decode_to_lua_type(lua_State *L, mp_cur *c);
 
@@ -466,34 +562,44 @@ void mp_decode_to_lua_hash(lua_State *L, mp_cur *c, size_t len) {
  * a Lua type, that is left as the only result on the stack. */
 void mp_decode_to_lua_type(lua_State *L, mp_cur *c) {
     mp_cur_need(c,1);
+
+    /* If we return more than 18 elements, we must resize the stack to
+     * fit all our return values.  But, there is no way to
+     * determine how many objects a msgpack will unpack to up front, so
+     * we request a +1 larger stack on each iteration (noop if stack is
+     * big enough, and when stack does require resize it doubles in size) */
+    luaL_checkstack(L, 1,
+        "too many return values at once; "
+        "use unpack_one or unpack_limit instead.");
+
     switch(c->p[0]) {
     case 0xcc:  /* uint 8 */
         mp_cur_need(c,2);
-        lua_pushnumber(L,c->p[1]);
+        lua_pushunsigned(L,c->p[1]);
         mp_cur_consume(c,2);
         break;
     case 0xd0:  /* int 8 */
         mp_cur_need(c,2);
-        lua_pushnumber(L,(char)c->p[1]);
+        lua_pushinteger(L,(char)c->p[1]);
         mp_cur_consume(c,2);
         break;
     case 0xcd:  /* uint 16 */
         mp_cur_need(c,3);
-        lua_pushnumber(L,
+        lua_pushunsigned(L,
             (c->p[1] << 8) |
              c->p[2]);
         mp_cur_consume(c,3);
         break;
     case 0xd1:  /* int 16 */
         mp_cur_need(c,3);
-        lua_pushnumber(L,(int16_t)
+        lua_pushinteger(L,(int16_t)
             (c->p[1] << 8) |
              c->p[2]);
         mp_cur_consume(c,3);
         break;
     case 0xce:  /* uint 32 */
         mp_cur_need(c,5);
-        lua_pushnumber(L,
+        lua_pushunsigned(L,
             ((uint32_t)c->p[1] << 24) |
             ((uint32_t)c->p[2] << 16) |
             ((uint32_t)c->p[3] << 8) |
@@ -502,7 +608,7 @@ void mp_decode_to_lua_type(lua_State *L, mp_cur *c) {
         break;
     case 0xd2:  /* int 32 */
         mp_cur_need(c,5);
-        lua_pushnumber(L,
+        lua_pushinteger(L,
             ((int32_t)c->p[1] << 24) |
             ((int32_t)c->p[2] << 16) |
             ((int32_t)c->p[3] << 8) |
@@ -511,7 +617,7 @@ void mp_decode_to_lua_type(lua_State *L, mp_cur *c) {
         break;
     case 0xcf:  /* uint 64 */
         mp_cur_need(c,9);
-        lua_pushnumber(L,
+        lua_pushunsigned(L,
             ((uint64_t)c->p[1] << 56) |
             ((uint64_t)c->p[2] << 48) |
             ((uint64_t)c->p[3] << 40) |
@@ -524,7 +630,7 @@ void mp_decode_to_lua_type(lua_State *L, mp_cur *c) {
         break;
     case 0xd3:  /* int 64 */
         mp_cur_need(c,9);
-        lua_pushnumber(L,
+        lua_pushinteger(L,
             ((int64_t)c->p[1] << 56) |
             ((int64_t)c->p[2] << 48) |
             ((int64_t)c->p[3] << 40) |
@@ -630,10 +736,10 @@ void mp_decode_to_lua_type(lua_State *L, mp_cur *c) {
         break;
     default:    /* types that can't be idenitified by first byte value. */
         if ((c->p[0] & 0x80) == 0) {   /* positive fixnum */
-            lua_pushnumber(L,c->p[0]);
+            lua_pushunsigned(L,c->p[0]);
             mp_cur_consume(c,1);
         } else if ((c->p[0] & 0xe0) == 0xe0) {  /* negative fixnum */
-            lua_pushnumber(L,(signed char)c->p[0]);
+            lua_pushinteger(L,(signed char)c->p[0]);
             mp_cur_consume(c,1);
         } else if ((c->p[0] & 0xe0) == 0xa0) {  /* fix raw */
             size_t l = c->p[0] & 0x1f;
@@ -654,54 +760,163 @@ void mp_decode_to_lua_type(lua_State *L, mp_cur *c) {
     }
 }
 
-static int mp_unpack(lua_State *L) {
+static int mp_unpack_full(lua_State *L, int limit, int offset) {
     size_t len;
-    const unsigned char *s;
-    mp_cur *c;
+    const char *s;
+    mp_cur c;
+    int cnt; /* Number of objects unpacked */
+    int decode_all = (!limit && !offset);
+
+    s = luaL_checklstring(L,1,&len); /* if no match, exits */
+
+    if (offset < 0 || limit < 0) /* requesting negative off or lim is invalid */
+        return luaL_error(L,
+            "Invalid request to unpack with offset of %d and limit of %d.",
+            offset, len);
+    else if (offset > len)
+        return luaL_error(L,
+            "Start offset %d greater than input length %d.", offset, len);
 
-    if (!lua_isstring(L,-1)) {
-        lua_pushstring(L,"MessagePack decoding needs a string as input.");
-        lua_error(L);
+    if (decode_all) limit = INT_MAX;
+
+    mp_cur_init(&c,(const unsigned char *)s+offset,len-offset);
+
+    /* We loop over the decode because this could be a stream
+     * of multiple top-level values serialized together */
+    for(cnt = 0; c.left > 0 && cnt < limit; cnt++) {
+        mp_decode_to_lua_type(L,&c);
+
+        if (c.err == MP_CUR_ERROR_EOF) {
+            return luaL_error(L,"Missing bytes in input.");
+        } else if (c.err == MP_CUR_ERROR_BADFMT) {
+            return luaL_error(L,"Bad data format in input.");
+        }
     }
 
-    s = (const unsigned char*) lua_tolstring(L,-1,&len);
-    c = mp_cur_new(s,len);
-    mp_decode_to_lua_type(L,c);
-    
-    if (c->err == MP_CUR_ERROR_EOF) {
-        mp_cur_free(c);
-        lua_pushstring(L,"Missing bytes in input.");
-        lua_error(L);
-    } else if (c->err == MP_CUR_ERROR_BADFMT) {
-        mp_cur_free(c);
-        lua_pushstring(L,"Bad data format in input.");
-        lua_error(L);
-    } else if (c->left != 0) {
-        mp_cur_free(c);
-        lua_pushstring(L,"Extra bytes in input.");
-        lua_error(L);
+    if (!decode_all) {
+        /* c->left is the remaining size of the input buffer.
+         * subtract the entire buffer size from the unprocessed size
+         * to get our next start offset */
+        int offset = len - c.left;
+        /* Return offset -1 when we have have processed the entire buffer. */
+        lua_pushinteger(L, c.left == 0 ? -1 : offset);
+        /* Results are returned with the arg elements still
+         * in place. Lua takes care of only returning
+         * elements above the args for us.
+         * In this case, we have one arg on the stack
+         * for this function, so we insert our first return
+         * value at position 2. */
+        lua_insert(L, 2);
+        cnt += 1; /* increase return count by one to make room for offset */
     }
-    mp_cur_free(c);
-    return 1;
+
+    return cnt;
 }
 
-/* ---------------------------------------------------------------------------- */
+static int mp_unpack(lua_State *L) {
+    return mp_unpack_full(L, 0, 0);
+}
+
+static int mp_unpack_one(lua_State *L) {
+    int offset = luaL_optint(L, 2, 0);
+    /* Variable pop because offset may not exist */
+    lua_pop(L, lua_gettop(L)-1);
+    return mp_unpack_full(L, 1, offset);
+}
+
+static int mp_unpack_limit(lua_State *L) {
+    int limit = luaL_checkint(L, 2);
+    int offset = luaL_optint(L, 3, 0);
+    /* Variable pop because offset may not exist */
+    lua_pop(L, lua_gettop(L)-1);
+
+    return mp_unpack_full(L, limit, offset);
+}
+
+static int mp_safe(lua_State *L) {
+    int argc, err, total_results;
+
+    argc = lua_gettop(L);
+
+    /* This adds our function to the bottom of the stack
+     * (the "call this function" position) */
+    lua_pushvalue(L, lua_upvalueindex(1));
+    lua_insert(L, 1);
+
+    err = lua_pcall(L, argc, LUA_MULTRET, 0);
+    total_results = lua_gettop(L);
+
+    if (!err) {
+        return total_results;
+    } else {
+        lua_pushnil(L);
+        lua_insert(L,-2);
+        return 2;
+    }
+}
 
-static const struct luaL_reg thislib[] = {
+/* -------------------------------------------------------------------------- */
+static const struct luaL_Reg cmds[] = {
     {"pack", mp_pack},
     {"unpack", mp_unpack},
-    {NULL, NULL}
+    {"unpack_one", mp_unpack_one},
+    {"unpack_limit", mp_unpack_limit},
+    {0}
 };
 
-LUALIB_API int luaopen_cmsgpack (lua_State *L) {
-    luaL_register(L, "cmsgpack", thislib);
+static int luaopen_create(lua_State *L) {
+    int i;
+    /* Manually construct our module table instead of
+     * relying on _register or _newlib */
+    lua_newtable(L);
+
+    for (i = 0; i < (sizeof(cmds)/sizeof(*cmds) - 1); i++) {
+        lua_pushcfunction(L, cmds[i].func);
+        lua_setfield(L, -2, cmds[i].name);
+    }
 
+    /* Add metadata */
+    lua_pushliteral(L, LUACMSGPACK_NAME);
+    lua_setfield(L, -2, "_NAME");
     lua_pushliteral(L, LUACMSGPACK_VERSION);
     lua_setfield(L, -2, "_VERSION");
     lua_pushliteral(L, LUACMSGPACK_COPYRIGHT);
     lua_setfield(L, -2, "_COPYRIGHT");
     lua_pushliteral(L, LUACMSGPACK_DESCRIPTION);
-    lua_setfield(L, -2, "_DESCRIPTION"); 
+    lua_setfield(L, -2, "_DESCRIPTION");
+    return 1;
+}
+
+LUALIB_API int luaopen_cmsgpack(lua_State *L) {
+    luaopen_create(L);
+
+#if LUA_VERSION_NUM < 502
+    /* Register name globally for 5.1 */
+    lua_pushvalue(L, -1);
+    lua_setglobal(L, LUACMSGPACK_NAME);
+#endif
+
+    return 1;
+}
+
+LUALIB_API int luaopen_cmsgpack_safe(lua_State *L) {
+    int i;
+
+    luaopen_cmsgpack(L);
+
+    /* Wrap all functions in the safe handler */
+    for (i = 0; i < (sizeof(cmds)/sizeof(*cmds) - 1); i++) {
+        lua_getfield(L, -1, cmds[i].name);
+        lua_pushcclosure(L, mp_safe, 1);
+        lua_setfield(L, -2, cmds[i].name);
+    }
+
+#if LUA_VERSION_NUM < 502
+    /* Register name globally for 5.1 */
+    lua_pushvalue(L, -1);
+    lua_setglobal(L, LUACMSGPACK_SAFE_NAME);
+#endif
+
     return 1;
 }
 