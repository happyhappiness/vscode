@@ -1,8 +1,6 @@
-#define VERSION "1.0.3"
-
-/* CJSON - JSON support for Lua
+/* Lua CJSON - JSON support for Lua
  *
- * Copyright (c) 2010-2011  Mark Pulford <mark@kyne.com.au>
+ * Copyright (c) 2010-2012  Mark Pulford <mark@kyne.com.au>
  *
  * Permission is hereby granted, free of charge, to any person obtaining
  * a copy of this software and associated documentation files (the
@@ -41,22 +39,40 @@
 #include <assert.h>
 #include <string.h>
 #include <math.h>
-#include "lua.h"
-#include "lauxlib.h"
+#include <limits.h>
+#include <lua.h>
+#include <lauxlib.h>
 
 #include "strbuf.h"
+#include "fpconv.h"
+
+#ifndef CJSON_MODNAME
+#define CJSON_MODNAME   "cjson"
+#endif
 
-#ifdef MISSING_ISINF
+#ifndef CJSON_VERSION
+#define CJSON_VERSION   "2.1.0"
+#endif
+
+/* Workaround for Solaris platforms missing isinf() */
+#if !defined(isinf) && (defined(USE_INTERNAL_ISINF) || defined(MISSING_ISINF))
 #define isinf(x) (!isnan(x) && isnan((x) - (x)))
 #endif
 
 #define DEFAULT_SPARSE_CONVERT 0
 #define DEFAULT_SPARSE_RATIO 2
 #define DEFAULT_SPARSE_SAFE 10
-#define DEFAULT_MAX_DEPTH 20
-#define DEFAULT_ENCODE_REFUSE_BADNUM 1
-#define DEFAULT_DECODE_REFUSE_BADNUM 0
+#define DEFAULT_ENCODE_MAX_DEPTH 1000
+#define DEFAULT_DECODE_MAX_DEPTH 1000
+#define DEFAULT_ENCODE_INVALID_NUMBERS 0
+#define DEFAULT_DECODE_INVALID_NUMBERS 1
 #define DEFAULT_ENCODE_KEEP_BUFFER 1
+#define DEFAULT_ENCODE_NUMBER_PRECISION 14
+
+#ifdef DISABLE_INVALID_NUMBERS
+#undef DEFAULT_DECODE_INVALID_NUMBERS
+#define DEFAULT_DECODE_INVALID_NUMBERS 0
+#endif
 
 typedef enum {
     T_OBJ_BEGIN,
@@ -96,29 +112,29 @@ static const char *json_token_type_name[] = {
 typedef struct {
     json_token_type_t ch2token[256];
     char escape2char[256];  /* Decoding */
-#if 0
-    char escapes[35][8];    /* Pre-generated escape string buffer */
-    char *char2escape[256]; /* Encoding */
-#endif
+
+    /* encode_buf is only allocated and used when
+     * encode_keep_buffer is set */
     strbuf_t encode_buf;
-    char number_fmt[8];     /* "%.XXg\0" */
-    int current_depth;
 
     int encode_sparse_convert;
     int encode_sparse_ratio;
     int encode_sparse_safe;
     int encode_max_depth;
-    int encode_refuse_badnum;
-    int decode_refuse_badnum;
-    int encode_keep_buffer;
+    int encode_invalid_numbers;     /* 2 => Encode as "null" */
     int encode_number_precision;
+    int encode_keep_buffer;
+
+    int decode_invalid_numbers;
+    int decode_max_depth;
 } json_config_t;
 
 typedef struct {
     const char *data;
-    int index;
+    const char *ptr;
     strbuf_t *tmp;    /* Temporary storage for strings */
     json_config_t *cfg;
+    int current_depth;
 } json_parse_t;
 
 typedef struct {
@@ -171,29 +187,76 @@ static const char *char2escape[256] = {
     NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
 };
 
-static int json_config_key;
-
 /* ===== CONFIGURATION ===== */
 
 static json_config_t *json_fetch_config(lua_State *l)
 {
     json_config_t *cfg;
 
-    lua_pushlightuserdata(l, &json_config_key);
-    lua_gettable(l, LUA_REGISTRYINDEX);
-    cfg = lua_touserdata(l, -1);
+    cfg = lua_touserdata(l, lua_upvalueindex(1));
     if (!cfg)
         luaL_error(l, "BUG: Unable to fetch CJSON configuration");
 
-    lua_pop(l, 1);
-
     return cfg;
 }
 
-static void json_verify_arg_count(lua_State *l, int args)
+/* Ensure the correct number of arguments have been provided.
+ * Pad with nil to allow other functions to simply check arg[i]
+ * to find whether an argument was provided */
+static json_config_t *json_arg_init(lua_State *l, int args)
 {
     luaL_argcheck(l, lua_gettop(l) <= args, args + 1,
                   "found too many arguments");
+
+    while (lua_gettop(l) < args)
+        lua_pushnil(l);
+
+    return json_fetch_config(l);
+}
+
+/* Process integer options for configuration functions */
+static int json_integer_option(lua_State *l, int optindex, int *setting,
+                               int min, int max)
+{
+    char errmsg[64];
+    int value;
+
+    if (!lua_isnil(l, optindex)) {
+        value = luaL_checkinteger(l, optindex);
+        snprintf(errmsg, sizeof(errmsg), "expected integer between %d and %d", min, max);
+        luaL_argcheck(l, min <= value && value <= max, 1, errmsg);
+        *setting = value;
+    }
+
+    lua_pushinteger(l, *setting);
+
+    return 1;
+}
+
+/* Process enumerated arguments for a configuration function */
+static int json_enum_option(lua_State *l, int optindex, int *setting,
+                            const char **options, int bool_true)
+{
+    static const char *bool_options[] = { "off", "on", NULL };
+
+    if (!options) {
+        options = bool_options;
+        bool_true = 1;
+    }
+
+    if (!lua_isnil(l, optindex)) {
+        if (bool_true && lua_isboolean(l, optindex))
+            *setting = lua_toboolean(l, optindex) * bool_true;
+        else
+            *setting = luaL_checkoption(l, optindex, NULL, options);
+    }
+
+    if (bool_true && (*setting == 0 || *setting == bool_true))
+        lua_pushboolean(l, *setting);
+    else
+        lua_pushstring(l, options[*setting]);
+
+    return 1;
 }
 
 /* Configures handling of extremely sparse arrays:
@@ -202,29 +265,11 @@ static void json_verify_arg_count(lua_State *l, int args)
  * safe: Always use an array when the max index <= safe */
 static int json_cfg_encode_sparse_array(lua_State *l)
 {
-    json_config_t *cfg;
-    int val;
-
-    json_verify_arg_count(l, 3);
-    cfg = json_fetch_config(l);
-
-    switch (lua_gettop(l)) {
-    case 3:
-        val = luaL_checkinteger(l, 3);
-        luaL_argcheck(l, val >= 0, 3, "expected integer >= 0");
-        cfg->encode_sparse_safe = val;
-    case 2:
-        val = luaL_checkinteger(l, 2);
-        luaL_argcheck(l, val >= 0, 2, "expected integer >= 0");
-        cfg->encode_sparse_ratio = val;
-    case 1:
-        luaL_argcheck(l, lua_isboolean(l, 1), 1, "expected boolean");
-        cfg->encode_sparse_convert = lua_toboolean(l, 1);
-    }
+    json_config_t *cfg = json_arg_init(l, 3);
 
-    lua_pushboolean(l, cfg->encode_sparse_convert);
-    lua_pushinteger(l, cfg->encode_sparse_ratio);
-    lua_pushinteger(l, cfg->encode_sparse_safe);
+    json_enum_option(l, 1, &cfg->encode_sparse_convert, NULL, 1);
+    json_integer_option(l, 2, &cfg->encode_sparse_ratio, 0, INT_MAX);
+    json_integer_option(l, 3, &cfg->encode_sparse_safe, 0, INT_MAX);
 
     return 3;
 }
@@ -233,108 +278,80 @@ static int json_cfg_encode_sparse_array(lua_State *l)
  * encoding */
 static int json_cfg_encode_max_depth(lua_State *l)
 {
-    json_config_t *cfg;
-    int depth;
-
-    json_verify_arg_count(l, 1);
-    cfg = json_fetch_config(l);
+    json_config_t *cfg = json_arg_init(l, 1);
 
-    if (lua_gettop(l)) {
-        depth = luaL_checkinteger(l, 1);
-        luaL_argcheck(l, depth > 0, 1, "expected positive integer");
-        cfg->encode_max_depth = depth;
-    }
-
-    lua_pushinteger(l, cfg->encode_max_depth);
-
-    return 1;
+    return json_integer_option(l, 1, &cfg->encode_max_depth, 1, INT_MAX);
 }
 
-static void json_set_number_precision(json_config_t *cfg, int prec)
+/* Configures the maximum number of nested arrays/objects allowed when
+ * encoding */
+static int json_cfg_decode_max_depth(lua_State *l)
 {
-    cfg->encode_number_precision = prec;
-    sprintf(cfg->number_fmt, "%%.%dg", prec);
+    json_config_t *cfg = json_arg_init(l, 1);
+
+    return json_integer_option(l, 1, &cfg->decode_max_depth, 1, INT_MAX);
 }
 
 /* Configures number precision when converting doubles to text */
 static int json_cfg_encode_number_precision(lua_State *l)
 {
-    json_config_t *cfg;
-    int precision;
-
-    json_verify_arg_count(l, 1);
-    cfg = json_fetch_config(l);
-
-    if (lua_gettop(l)) {
-        precision = luaL_checkinteger(l, 1);
-        luaL_argcheck(l, 1 <= precision && precision <= 14, 1,
-                      "expected integer between 1 and 14");
-        json_set_number_precision(cfg, precision);
-    }
+    json_config_t *cfg = json_arg_init(l, 1);
 
-    lua_pushinteger(l, cfg->encode_number_precision);
-
-    return 1;
+    return json_integer_option(l, 1, &cfg->encode_number_precision, 1, 14);
 }
 
 /* Configures JSON encoding buffer persistence */
 static int json_cfg_encode_keep_buffer(lua_State *l)
 {
-    json_config_t *cfg;
+    json_config_t *cfg = json_arg_init(l, 1);
+    int old_value;
 
-    json_verify_arg_count(l, 1);
-    cfg = json_fetch_config(l);
+    old_value = cfg->encode_keep_buffer;
 
-    if (lua_gettop(l)) {
-        luaL_checktype(l, 1, LUA_TBOOLEAN);
-        cfg->encode_keep_buffer = lua_toboolean(l, 1);
-    }
+    json_enum_option(l, 1, &cfg->encode_keep_buffer, NULL, 1);
 
-    lua_pushboolean(l, cfg->encode_keep_buffer);
+    /* Init / free the buffer if the setting has changed */
+    if (old_value ^ cfg->encode_keep_buffer) {
+        if (cfg->encode_keep_buffer)
+            strbuf_init(&cfg->encode_buf, 0);
+        else
+            strbuf_free(&cfg->encode_buf);
+    }
 
     return 1;
 }
 
-/* On argument: decode enum and set config variables
- * **options must point to a NULL terminated array of 4 enums
- * Returns: current enum value */
-static void json_enum_option(lua_State *l, const char **options,
-                             int *opt1, int *opt2)
+#if defined(DISABLE_INVALID_NUMBERS) && !defined(USE_INTERNAL_FPCONV)
+void json_verify_invalid_number_setting(lua_State *l, int *setting)
 {
-    int setting;
+    if (*setting == 1) {
+        *setting = 0;
+        luaL_error(l, "Infinity, NaN, and/or hexadecimal numbers are not supported.");
+    }
+}
+#else
+#define json_verify_invalid_number_setting(l, s)    do { } while(0)
+#endif
 
-    if (lua_gettop(l)) {
-        if (lua_isboolean(l, 1))
-            setting = lua_toboolean(l, 1) * 3;
-        else
-            setting = luaL_checkoption(l, 1, NULL, options);
+static int json_cfg_encode_invalid_numbers(lua_State *l)
+{
+    static const char *options[] = { "off", "on", "null", NULL };
+    json_config_t *cfg = json_arg_init(l, 1);
 
-        *opt1 = setting & 1 ? 1 : 0;
-        *opt2 = setting & 2 ? 1 : 0;
-    } else {
-        setting = *opt1 | (*opt2 << 1);
-    }
+    json_enum_option(l, 1, &cfg->encode_invalid_numbers, options, 1);
 
-    if (setting)
-        lua_pushstring(l, options[setting]);
-    else
-        lua_pushboolean(l, 0);
-}
+    json_verify_invalid_number_setting(l, &cfg->encode_invalid_numbers);
 
+    return 1;
+}
 
-/* When enabled, rejects: NaN, Infinity, hexidecimal numbers */
-static int json_cfg_refuse_invalid_numbers(lua_State *l)
+static int json_cfg_decode_invalid_numbers(lua_State *l)
 {
-    static const char *options_enc_dec[] = { "none", "encode", "decode",
-                                             "both", NULL };
-    json_config_t *cfg;
+    json_config_t *cfg = json_arg_init(l, 1);
 
-    json_verify_arg_count(l, 1);
-    cfg = json_fetch_config(l);
+    json_enum_option(l, 1, &cfg->decode_invalid_numbers, NULL, 1);
 
-    json_enum_option(l, options_enc_dec,
-                     &cfg->encode_refuse_badnum,
-                     &cfg->decode_refuse_badnum);
+    json_verify_invalid_number_setting(l, &cfg->encode_invalid_numbers);
 
     return 1;
 }
@@ -364,16 +381,19 @@ static void json_create_config(lua_State *l)
     lua_setfield(l, -2, "__gc");
     lua_setmetatable(l, -2);
 
-    strbuf_init(&cfg->encode_buf, 0);
-
     cfg->encode_sparse_convert = DEFAULT_SPARSE_CONVERT;
     cfg->encode_sparse_ratio = DEFAULT_SPARSE_RATIO;
     cfg->encode_sparse_safe = DEFAULT_SPARSE_SAFE;
-    cfg->encode_max_depth = DEFAULT_MAX_DEPTH;
-    cfg->encode_refuse_badnum = DEFAULT_ENCODE_REFUSE_BADNUM;
-    cfg->decode_refuse_badnum = DEFAULT_DECODE_REFUSE_BADNUM;
+    cfg->encode_max_depth = DEFAULT_ENCODE_MAX_DEPTH;
+    cfg->decode_max_depth = DEFAULT_DECODE_MAX_DEPTH;
+    cfg->encode_invalid_numbers = DEFAULT_ENCODE_INVALID_NUMBERS;
+    cfg->decode_invalid_numbers = DEFAULT_DECODE_INVALID_NUMBERS;
     cfg->encode_keep_buffer = DEFAULT_ENCODE_KEEP_BUFFER;
-    json_set_number_precision(cfg, 14);
+    cfg->encode_number_precision = DEFAULT_ENCODE_NUMBER_PRECISION;
+
+#if DEFAULT_ENCODE_KEEP_BUFFER > 0
+    strbuf_init(&cfg->encode_buf, 0);
+#endif
 
     /* Decoding init */
 
@@ -419,41 +439,15 @@ static void json_create_config(lua_State *l)
     cfg->escape2char['f'] = '\f';
     cfg->escape2char['r'] = '\r';
     cfg->escape2char['u'] = 'u';          /* Unicode parsing required */
-
-
-#if 0
-    /* Initialise separate storage for pre-generated escape codes.
-     * Escapes 0-31 map directly, 34, 92, 127 follow afterwards to
-     * save memory. */
-    for (i = 0 ; i < 32; i++)
-        sprintf(cfg->escapes[i], "\\u%04x", i);
-    strcpy(cfg->escapes[8], "\b");              /* Override simpler escapes */
-    strcpy(cfg->escapes[9], "\t");
-    strcpy(cfg->escapes[10], "\n");
-    strcpy(cfg->escapes[12], "\f");
-    strcpy(cfg->escapes[13], "\r");
-    strcpy(cfg->escapes[32], "\\\"");           /* chr(34) */
-    strcpy(cfg->escapes[33], "\\\\");           /* chr(92) */
-    sprintf(cfg->escapes[34], "\\u%04x", 127);  /* char(127) */
-
-    /* Initialise encoding escape lookup table */
-    for (i = 0; i < 32; i++)
-        cfg->char2escape[i] = cfg->escapes[i];
-    for (i = 32; i < 256; i++)
-        cfg->char2escape[i] = NULL;
-    cfg->char2escape[34] = cfg->escapes[32];
-    cfg->char2escape[92] = cfg->escapes[33];
-    cfg->char2escape[127] = cfg->escapes[34];
-#endif
 }
 
 /* ===== ENCODING ===== */
 
-static void json_encode_exception(lua_State *l, json_config_t *cfg, int lindex,
+static void json_encode_exception(lua_State *l, json_config_t *cfg, strbuf_t *json, int lindex,
                                   const char *reason)
 {
     if (!cfg->encode_keep_buffer)
-        strbuf_free(&cfg->encode_buf);
+        strbuf_free(json);
     luaL_error(l, "Cannot serialise %s: %s",
                   lua_typename(l, lua_type(l, lindex)), reason);
 }
@@ -494,7 +488,7 @@ static void json_append_string(lua_State *l, strbuf_t *json, int lindex)
  * -1   object (not a pure array)
  * >=0  elements in array
  */
-static int lua_array_length(lua_State *l, json_config_t *cfg)
+static int lua_array_length(lua_State *l, json_config_t *cfg, strbuf_t *json)
 {
     double k;
     int max;
@@ -529,39 +523,49 @@ static int lua_array_length(lua_State *l, json_config_t *cfg)
         max > items * cfg->encode_sparse_ratio &&
         max > cfg->encode_sparse_safe) {
         if (!cfg->encode_sparse_convert)
-            json_encode_exception(l, cfg, -1, "excessively sparse array");
+            json_encode_exception(l, cfg, json, -1, "excessively sparse array");
 
         return -1;
     }
 
     return max;
 }
 
-static void json_encode_descend(lua_State *l, json_config_t *cfg)
+static void json_check_encode_depth(lua_State *l, json_config_t *cfg,
+                                    int current_depth, strbuf_t *json)
 {
-    cfg->current_depth++;
+    /* Ensure there are enough slots free to traverse a table (key,
+     * value) and push a string for a potential error message.
+     *
+     * Unlike "decode", the key and value are still on the stack when
+     * lua_checkstack() is called.  Hence an extra slot for luaL_error()
+     * below is required just in case the next check to lua_checkstack()
+     * fails.
+     *
+     * While this won't cause a crash due to the EXTRA_STACK reserve
+     * slots, it would still be an improper use of the API. */
+    if (current_depth <= cfg->encode_max_depth && lua_checkstack(l, 3))
+        return;
 
-    if (cfg->current_depth > cfg->encode_max_depth) {
-        if (!cfg->encode_keep_buffer)
-            strbuf_free(&cfg->encode_buf);
-        luaL_error(l, "Cannot serialise, excessive nesting (%d)",
-                   cfg->current_depth);
-    }
+    if (!cfg->encode_keep_buffer)
+        strbuf_free(json);
+
+    luaL_error(l, "Cannot serialise, excessive nesting (%d)",
+               current_depth);
 }
 
-static void json_append_data(lua_State *l, json_config_t *cfg, strbuf_t *json);
+static void json_append_data(lua_State *l, json_config_t *cfg,
+                             int current_depth, strbuf_t *json);
 
 /* json_append_array args:
  * - lua_State
  * - JSON strbuf
  * - Size of passwd Lua array (top of stack) */
-static void json_append_array(lua_State *l, json_config_t *cfg, strbuf_t *json,
-                              int array_length)
+static void json_append_array(lua_State *l, json_config_t *cfg, int current_depth,
+                              strbuf_t *json, int array_length)
 {
     int comma, i;
 
-    json_encode_descend(l, cfg);
-
     strbuf_append_char(json, '[');
 
     comma = 0;
@@ -572,38 +576,48 @@ static void json_append_array(lua_State *l, json_config_t *cfg, strbuf_t *json,
             comma = 1;
 
         lua_rawgeti(l, -1, i);
-        json_append_data(l, cfg, json);
+        json_append_data(l, cfg, current_depth, json);
         lua_pop(l, 1);
     }
 
     strbuf_append_char(json, ']');
-
-    cfg->current_depth--;
 }
 
-static void json_append_number(lua_State *l, strbuf_t *json, int index,
-                               json_config_t *cfg)
+static void json_append_number(lua_State *l, json_config_t *cfg,
+                               strbuf_t *json, int lindex)
 {
-    double num = lua_tonumber(l, index);
+    double num = lua_tonumber(l, lindex);
+    int len;
 
-    if (cfg->encode_refuse_badnum && (isinf(num) || isnan(num)))
-        json_encode_exception(l, cfg, index, "must not be NaN or Inf");
+    if (cfg->encode_invalid_numbers == 0) {
+        /* Prevent encoding invalid numbers */
+        if (isinf(num) || isnan(num))
+            json_encode_exception(l, cfg, json, lindex, "must not be NaN or Inf");
+    } else if (cfg->encode_invalid_numbers == 1) {
+        /* Encode invalid numbers, but handle "nan" separately
+         * since some platforms may encode as "-nan". */
+        if (isnan(num)) {
+            strbuf_append_mem(json, "nan", 3);
+            return;
+        }
+    } else {
+        /* Encode invalid numbers as "null" */
+        if (isinf(num) || isnan(num)) {
+            strbuf_append_mem(json, "null", 4);
+            return;
+        }
+    }
 
-    /* Lowest double printed with %.14g is 21 characters long:
-     * -1.7976931348623e+308
-     *
-     * Use 32 to include the \0, and a few extra just in case..
-     */
-    strbuf_append_fmt(json, 32, cfg->number_fmt, num);
+    strbuf_ensure_empty_length(json, FPCONV_G_FMT_BUFSIZE);
+    len = fpconv_g_fmt(strbuf_empty_ptr(json), num, cfg->encode_number_precision);
+    strbuf_extend_length(json, len);
 }
 
 static void json_append_object(lua_State *l, json_config_t *cfg,
-                               strbuf_t *json)
+                               int current_depth, strbuf_t *json)
 {
     int comma, keytype;
 
-    json_encode_descend(l, cfg);
-
     /* Object */
     strbuf_append_char(json, '{');
 
@@ -620,30 +634,29 @@ static void json_append_object(lua_State *l, json_config_t *cfg,
         keytype = lua_type(l, -2);
         if (keytype == LUA_TNUMBER) {
             strbuf_append_char(json, '"');
-            json_append_number(l, json, -2, cfg);
+            json_append_number(l, cfg, json, -2);
             strbuf_append_mem(json, "\":", 2);
         } else if (keytype == LUA_TSTRING) {
             json_append_string(l, json, -2);
             strbuf_append_char(json, ':');
         } else {
-            json_encode_exception(l, cfg, -2,
+            json_encode_exception(l, cfg, json, -2,
                                   "table key must be a number or string");
             /* never returns */
         }
 
         /* table, key, value */
-        json_append_data(l, cfg, json);
+        json_append_data(l, cfg, current_depth, json);
         lua_pop(l, 1);
         /* table, key */
     }
 
     strbuf_append_char(json, '}');
-
-    cfg->current_depth--;
 }
 
 /* Serialise Lua data into JSON string. */
-static void json_append_data(lua_State *l, json_config_t *cfg, strbuf_t *json)
+static void json_append_data(lua_State *l, json_config_t *cfg,
+                             int current_depth, strbuf_t *json)
 {
     int len;
 
@@ -652,7 +665,7 @@ static void json_append_data(lua_State *l, json_config_t *cfg, strbuf_t *json)
         json_append_string(l, json, -1);
         break;
     case LUA_TNUMBER:
-        json_append_number(l, json, -1, cfg);
+        json_append_number(l, cfg, json, -1);
         break;
     case LUA_TBOOLEAN:
         if (lua_toboolean(l, -1))
@@ -661,11 +674,13 @@ static void json_append_data(lua_State *l, json_config_t *cfg, strbuf_t *json)
             strbuf_append_mem(json, "false", 5);
         break;
     case LUA_TTABLE:
-        len = lua_array_length(l, cfg);
+        current_depth++;
+        json_check_encode_depth(l, cfg, current_depth, json);
+        len = lua_array_length(l, cfg, json);
         if (len > 0)
-            json_append_array(l, cfg, json, len);
+            json_append_array(l, cfg, current_depth, json, len);
         else
-            json_append_object(l, cfg, json);
+            json_append_object(l, cfg, current_depth, json);
         break;
     case LUA_TNIL:
         strbuf_append_mem(json, "null", 4);
@@ -678,38 +693,38 @@ static void json_append_data(lua_State *l, json_config_t *cfg, strbuf_t *json)
     default:
         /* Remaining types (LUA_TFUNCTION, LUA_TUSERDATA, LUA_TTHREAD,
          * and LUA_TLIGHTUSERDATA) cannot be serialised */
-        json_encode_exception(l, cfg, -1, "type not supported");
+        json_encode_exception(l, cfg, json, -1, "type not supported");
         /* never returns */
     }
 }
 
 static int json_encode(lua_State *l)
 {
-    json_config_t *cfg;
+    json_config_t *cfg = json_fetch_config(l);
+    strbuf_t local_encode_buf;
+    strbuf_t *encode_buf;
     char *json;
     int len;
 
-    /* Can't use json_verify_arg_count() since we need to ensure
-     * there is only 1 argument */
     luaL_argcheck(l, lua_gettop(l) == 1, 1, "expected 1 argument");
 
-    cfg = json_fetch_config(l);
-    cfg->current_depth = 0;
-
-    /* Reset the persistent buffer if it exists.
-     * Otherwise allocate a new buffer. */
-    if (strbuf_allocated(&cfg->encode_buf))
-        strbuf_reset(&cfg->encode_buf);
-    else
-        strbuf_init(&cfg->encode_buf, 0);
+    if (!cfg->encode_keep_buffer) {
+        /* Use private buffer */
+        encode_buf = &local_encode_buf;
+        strbuf_init(encode_buf, 0);
+    } else {
+        /* Reuse existing buffer */
+        encode_buf = &cfg->encode_buf;
+        strbuf_reset(encode_buf);
+    }
 
-    json_append_data(l, cfg, &cfg->encode_buf);
-    json = strbuf_string(&cfg->encode_buf, &len);
+    json_append_data(l, cfg, 0, encode_buf);
+    json = strbuf_string(encode_buf, &len);
 
     lua_pushlstring(l, json, len);
 
     if (!cfg->encode_keep_buffer)
-        strbuf_free(&cfg->encode_buf);
+        strbuf_free(encode_buf);
 
     return 1;
 }
@@ -808,7 +823,7 @@ static int json_append_unicode_escape(json_parse_t *json)
     int escape_len = 6;
 
     /* Fetch UTF-16 code unit */
-    codepoint = decode_hex4(&json->data[json->index + 2]);
+    codepoint = decode_hex4(json->ptr + 2);
     if (codepoint < 0)
         return -1;
 
@@ -824,13 +839,13 @@ static int json_append_unicode_escape(json_parse_t *json)
             return -1;
 
         /* Ensure the next code is a unicode escape */
-        if (json->data[json->index + escape_len] != '\\' ||
-            json->data[json->index + escape_len + 1] != 'u') {
+        if (*(json->ptr + escape_len) != '\\' ||
+            *(json->ptr + escape_len + 1) != 'u') {
             return -1;
         }
 
         /* Fetch the next codepoint */
-        surrogate_low = decode_hex4(&json->data[json->index + 2 + escape_len]);
+        surrogate_low = decode_hex4(json->ptr + 2 + escape_len);
         if (surrogate_low < 0)
             return -1;
 
@@ -852,7 +867,7 @@ static int json_append_unicode_escape(json_parse_t *json)
 
     /* Append bytes and advance parse index */
     strbuf_append_mem_unsafe(json->tmp, utf8, len);
-    json->index += escape_len;
+    json->ptr += escape_len;
 
     return 0;
 }
@@ -861,7 +876,7 @@ static void json_set_token_error(json_token_t *token, json_parse_t *json,
                                  const char *errtype)
 {
     token->type = T_ERROR;
-    token->index = json->index;
+    token->index = json->ptr - json->data;
     token->value.string = errtype;
 }
 
@@ -871,15 +886,18 @@ static void json_next_string_token(json_parse_t *json, json_token_t *token)
     char ch;
 
     /* Caller must ensure a string is next */
-    assert(json->data[json->index] == '"');
+    assert(*json->ptr == '"');
 
     /* Skip " */
-    json->index++;
+    json->ptr++;
 
     /* json->tmp is the temporary strbuf used to accumulate the
-     * decoded string value. */
+     * decoded string value.
+     * json->tmp is sized to handle JSON containing only a string value.
+     */
     strbuf_reset(json->tmp);
-    while ((ch = json->data[json->index]) != '"') {
+
+    while ((ch = *json->ptr) != '"') {
         if (!ch) {
             /* Premature end of the string */
             json_set_token_error(token, json, "unexpected end of string");
@@ -889,7 +907,7 @@ static void json_next_string_token(json_parse_t *json, json_token_t *token)
         /* Handle escapes */
         if (ch == '\\') {
             /* Fetch escape character */
-            ch = json->data[json->index + 1];
+            ch = *(json->ptr + 1);
 
             /* Translate escape code and append to tmp string */
             ch = escape2char[(unsigned char)ch];
@@ -907,14 +925,14 @@ static void json_next_string_token(json_parse_t *json, json_token_t *token)
             }
 
             /* Skip '\' */
-            json->index++;
+            json->ptr++;
         }
         /* Append normal character or translated single character
          * Unicode escapes are handled above */
         strbuf_append_char_unsafe(json->tmp, ch);
-        json->index++;
+        json->ptr++;
     }
-    json->index++;  /* Eat final quote (") */
+    json->ptr++;    /* Eat final quote (") */
 
     strbuf_ensure_null(json->tmp);
 
@@ -928,7 +946,7 @@ static void json_next_string_token(json_parse_t *json, json_token_t *token)
  * json_next_number_token() uses strtod() which allows other forms:
  * - numbers starting with '+'
  * - NaN, -NaN, infinity, -infinity
- * - hexidecimal numbers
+ * - hexadecimal numbers
  * - numbers with leading zeros
  *
  * json_is_invalid_number() detects "numbers" which may pass strtod()'s
@@ -939,34 +957,33 @@ static void json_next_string_token(json_parse_t *json, json_token_t *token)
  */
 static int json_is_invalid_number(json_parse_t *json)
 {
-    int i = json->index;
+    const char *p = json->ptr;
 
     /* Reject numbers starting with + */
-    if (json->data[i] == '+')
+    if (*p == '+')
         return 1;
 
     /* Skip minus sign if it exists */
-    if (json->data[i] == '-')
-        i++;
+    if (*p == '-')
+        p++;
 
     /* Reject numbers starting with 0x, or leading zeros */
-    if (json->data[i] == '0') {
-        int ch2 = json->data[i + 1];
+    if (*p == '0') {
+        int ch2 = *(p + 1);
 
         if ((ch2 | 0x20) == 'x' ||          /* Hex */
             ('0' <= ch2 && ch2 <= '9'))     /* Leading zero */
             return 1;
 
         return 0;
-    } else if (json->data[i] <= '9') {
+    } else if (*p <= '9') {
         return 0;                           /* Ordinary number */
     }
 
-
     /* Reject inf/nan */
-    if (!strncasecmp(&json->data[i], "inf", 3))
+    if (!strncasecmp(p, "inf", 3))
         return 1;
-    if (!strncasecmp(&json->data[i], "nan", 3))
+    if (!strncasecmp(p, "nan", 3))
         return 1;
 
     /* Pass all other numbers which may still be invalid, but
@@ -976,35 +993,39 @@ static int json_is_invalid_number(json_parse_t *json)
 
 static void json_next_number_token(json_parse_t *json, json_token_t *token)
 {
-    const char *startptr;
     char *endptr;
 
     token->type = T_NUMBER;
-    startptr = &json->data[json->index];
-    token->value.number = strtod(&json->data[json->index], &endptr);
-    if (startptr == endptr)
+    token->value.number = fpconv_strtod(json->ptr, &endptr);
+    if (json->ptr == endptr)
         json_set_token_error(token, json, "invalid number");
     else
-        json->index += endptr - startptr;   /* Skip the processed number */
+        json->ptr = endptr;     /* Skip the processed number */
 
     return;
 }
 
 /* Fills in the token struct.
  * T_STRING will return a pointer to the json_parse_t temporary string
- * T_ERROR will leave the json->index pointer at the error.
+ * T_ERROR will leave the json->ptr pointer at the error.
  */
 static void json_next_token(json_parse_t *json, json_token_t *token)
 {
-    json_token_type_t *ch2token = json->cfg->ch2token;
+    const json_token_type_t *ch2token = json->cfg->ch2token;
     int ch;
 
-    /* Eat whitespace. FIXME: UGLY */
-    token->type = ch2token[(unsigned char)json->data[json->index]];
-    while (token->type == T_WHITESPACE)
-        token->type = ch2token[(unsigned char)json->data[++json->index]];
+    /* Eat whitespace. */
+    while (1) {
+        ch = (unsigned char)*(json->ptr);
+        token->type = ch2token[ch];
+        if (token->type != T_WHITESPACE)
+            break;
+        json->ptr++;
+    }
 
-    token->index = json->index;
+    /* Store location of new token. Required when throwing errors
+     * for unexpected tokens (syntax errors). */
+    token->index = json->ptr - json->data;
 
     /* Don't advance the pointer for an error or the end */
     if (token->type == T_ERROR) {
@@ -1018,44 +1039,43 @@ static void json_next_token(json_parse_t *json, json_token_t *token)
 
     /* Found a known single character token, advance index and return */
     if (token->type != T_UNKNOWN) {
-        json->index++;
+        json->ptr++;
         return;
     }
 
-    /* Process characters which triggered T_UNKNOWN */
-    ch = json->data[json->index];
-
-    /* Must use strncmp() to match the front of the JSON string.
+    /* Process characters which triggered T_UNKNOWN
+     *
+     * Must use strncmp() to match the front of the JSON string.
      * JSON identifier must be lowercase.
      * When strict_numbers if disabled, either case is allowed for
      * Infinity/NaN (since we are no longer following the spec..) */
     if (ch == '"') {
         json_next_string_token(json, token);
         return;
     } else if (ch == '-' || ('0' <= ch && ch <= '9')) {
-        if (json->cfg->decode_refuse_badnum && json_is_invalid_number(json)) {
+        if (!json->cfg->decode_invalid_numbers && json_is_invalid_number(json)) {
             json_set_token_error(token, json, "invalid number");
             return;
         }
         json_next_number_token(json, token);
         return;
-    } else if (!strncmp(&json->data[json->index], "true", 4)) {
+    } else if (!strncmp(json->ptr, "true", 4)) {
         token->type = T_BOOLEAN;
         token->value.boolean = 1;
-        json->index += 4;
+        json->ptr += 4;
         return;
-    } else if (!strncmp(&json->data[json->index], "false", 5)) {
+    } else if (!strncmp(json->ptr, "false", 5)) {
         token->type = T_BOOLEAN;
         token->value.boolean = 0;
-        json->index += 5;
+        json->ptr += 5;
         return;
-    } else if (!strncmp(&json->data[json->index], "null", 4)) {
+    } else if (!strncmp(json->ptr, "null", 4)) {
         token->type = T_NULL;
-        json->index += 4;
+        json->ptr += 4;
         return;
-    } else if (!json->cfg->decode_refuse_badnum &&
+    } else if (json->cfg->decode_invalid_numbers &&
                json_is_invalid_number(json)) {
-        /* When refuse_badnum is disabled, only attempt to process
+        /* When decode_invalid_numbers is enabled, only attempt to process
          * numbers we know are invalid JSON (Inf, NaN, hex)
          * This is required to generate an appropriate token error,
          * otherwise all bad tokens will register as "invalid number"
@@ -1091,13 +1111,23 @@ static void json_throw_parse_error(lua_State *l, json_parse_t *json,
                exp, found, token->index + 1);
 }
 
-static void json_decode_checkstack(lua_State *l, json_parse_t *json, int n)
+static inline void json_decode_ascend(json_parse_t *json)
 {
-    if (lua_checkstack(l, n))
+    json->current_depth--;
+}
+
+static void json_decode_descend(lua_State *l, json_parse_t *json, int slots)
+{
+    json->current_depth++;
+
+    if (json->current_depth <= json->cfg->decode_max_depth &&
+        lua_checkstack(l, slots)) {
         return;
+    }
 
     strbuf_free(json->tmp);
-    luaL_error(l, "Too many nested data structures");
+    luaL_error(l, "Found too many nested data structures (%d) at character %d",
+        json->current_depth, json->ptr - json->data);
 }
 
 static void json_parse_object_context(lua_State *l, json_parse_t *json)
@@ -1106,14 +1136,15 @@ static void json_parse_object_context(lua_State *l, json_parse_t *json)
 
     /* 3 slots required:
      * .., table, key, value */
-    json_decode_checkstack(l, json, 3);
+    json_decode_descend(l, json, 3);
 
     lua_newtable(l);
 
     json_next_token(json, &token);
 
     /* Handle empty objects */
     if (token.type == T_OBJ_END) {
+        json_decode_ascend(json);
         return;
     }
 
@@ -1137,8 +1168,10 @@ static void json_parse_object_context(lua_State *l, json_parse_t *json)
 
         json_next_token(json, &token);
 
-        if (token.type == T_OBJ_END)
+        if (token.type == T_OBJ_END) {
+            json_decode_ascend(json);
             return;
+        }
 
         if (token.type != T_COMMA)
             json_throw_parse_error(l, json, "comma or object end", &token);
@@ -1155,24 +1188,28 @@ static void json_parse_array_context(lua_State *l, json_parse_t *json)
 
     /* 2 slots required:
      * .., table, value */
-    json_decode_checkstack(l, json, 2);
+    json_decode_descend(l, json, 2);
 
     lua_newtable(l);
 
     json_next_token(json, &token);
 
     /* Handle empty arrays */
-    if (token.type == T_ARR_END)
+    if (token.type == T_ARR_END) {
+        json_decode_ascend(json);
         return;
+    }
 
     for (i = 1; ; i++) {
         json_process_value(l, json, &token);
         lua_rawseti(l, -2, i);            /* arr[i] = value */
 
         json_next_token(json, &token);
 
-        if (token.type == T_ARR_END)
+        if (token.type == T_ARR_END) {
+            json_decode_ascend(json);
             return;
+        }
 
         if (token.type != T_COMMA)
             json_throw_parse_error(l, json, "comma or array end", &token);
@@ -1211,15 +1248,26 @@ static void json_process_value(lua_State *l, json_parse_t *json,
     }
 }
 
-/* json_text must be null terminated string */
-static void lua_json_decode(lua_State *l, const char *json_text, int json_len)
+static int json_decode(lua_State *l)
 {
     json_parse_t json;
     json_token_t token;
+    size_t json_len;
+
+    luaL_argcheck(l, lua_gettop(l) == 1, 1, "expected 1 argument");
 
     json.cfg = json_fetch_config(l);
-    json.data = json_text;
-    json.index = 0;
+    json.data = luaL_checklstring(l, 1, &json_len);
+    json.current_depth = 0;
+    json.ptr = json.data;
+
+    /* Detect Unicode other than UTF-8 (see RFC 4627, Sec 3)
+     *
+     * CJSON can support any simple data type, hence only the first
+     * character is guaranteed to be ASCII (at worst: '"'). This is
+     * still enough to detect whether the wrong encoding is in use. */
+    if (json_len >= 2 && (!json.data[0] || !json.data[1]))
+        luaL_error(l, "JSON parser does not support UTF-16 or UTF-32");
 
     /* Ensure the temporary buffer can hold the entire string.
      * This means we no longer need to do length checks since the decoded
@@ -1236,64 +1284,142 @@ static void lua_json_decode(lua_State *l, const char *json_text, int json_len)
         json_throw_parse_error(l, &json, "the end", &token);
 
     strbuf_free(json.tmp);
+
+    return 1;
 }
 
-static int json_decode(lua_State *l)
+/* ===== INITIALISATION ===== */
+
+#if !defined(LUA_VERSION_NUM) || LUA_VERSION_NUM < 502
+/* Compatibility for Lua 5.1.
+ *
+ * luaL_setfuncs() is used to create a module table where the functions have
+ * json_config_t as their first upvalue. Code borrowed from Lua 5.2 source. */
+static void luaL_setfuncs (lua_State *l, const luaL_Reg *reg, int nup)
 {
-    const char *json;
-    size_t len;
+    int i;
 
-    json_verify_arg_count(l, 1);
+    luaL_checkstack(l, nup, "too many upvalues");
+    for (; reg->name != NULL; reg++) {  /* fill the table with given functions */
+        for (i = 0; i < nup; i++)  /* copy upvalues to the top */
+            lua_pushvalue(l, -nup);
+        lua_pushcclosure(l, reg->func, nup);  /* closure with those upvalues */
+        lua_setfield(l, -(nup + 2), reg->name);
+    }
+    lua_pop(l, nup);  /* remove upvalues */
+}
+#endif
 
-    json = luaL_checklstring(l, 1, &len);
+/* Call target function in protected mode with all supplied args.
+ * Assumes target function only returns a single non-nil value.
+ * Convert and return thrown errors as: nil, "error message" */
+static int json_protect_conversion(lua_State *l)
+{
+    int err;
 
-    /* Detect Unicode other than UTF-8 (see RFC 4627, Sec 3)
-     *
-     * CJSON can support any simple data type, hence only the first
-     * character is guaranteed to be ASCII (at worst: '"'). This is
-     * still enough to detect whether the wrong encoding is in use. */
-    if (len >= 2 && (!json[0] || !json[1]))
-        luaL_error(l, "JSON parser does not support UTF-16 or UTF-32");
+    /* Deliberately throw an error for invalid arguments */
+    luaL_argcheck(l, lua_gettop(l) == 1, 1, "expected 1 argument");
 
-    lua_json_decode(l, json, len);
+    /* pcall() the function stored as upvalue(1) */
+    lua_pushvalue(l, lua_upvalueindex(1));
+    lua_insert(l, 1);
+    err = lua_pcall(l, 1, 1, 0);
+    if (!err)
+        return 1;
 
-    return 1;
-}
+    if (err == LUA_ERRRUN) {
+        lua_pushnil(l);
+        lua_insert(l, -2);
+        return 2;
+    }
 
-/* ===== INITIALISATION ===== */
+    /* Since we are not using a custom error handler, the only remaining
+     * errors are memory related */
+    return luaL_error(l, "Memory allocation error in CJSON protected call");
+}
 
-int luaopen_cjson(lua_State *l)
+/* Return cjson module table */
+static int lua_cjson_new(lua_State *l)
 {
     luaL_Reg reg[] = {
         { "encode", json_encode },
         { "decode", json_decode },
         { "encode_sparse_array", json_cfg_encode_sparse_array },
         { "encode_max_depth", json_cfg_encode_max_depth },
+        { "decode_max_depth", json_cfg_decode_max_depth },
         { "encode_number_precision", json_cfg_encode_number_precision },
         { "encode_keep_buffer", json_cfg_encode_keep_buffer },
-        { "refuse_invalid_numbers", json_cfg_refuse_invalid_numbers },
+        { "encode_invalid_numbers", json_cfg_encode_invalid_numbers },
+        { "decode_invalid_numbers", json_cfg_decode_invalid_numbers },
+        { "new", lua_cjson_new },
         { NULL, NULL }
     };
 
-    /* Use json_fetch_config as a pointer.
-     * It's faster than using a config string, and more unique */
-    lua_pushlightuserdata(l, &json_config_key);
-    json_create_config(l);
-    lua_settable(l, LUA_REGISTRYINDEX);
+    /* Initialise number conversions */
+    fpconv_init();
 
-    luaL_register(l, "cjson", reg);
+    /* cjson module table */
+    lua_newtable(l);
+
+    /* Register functions with config data as upvalue */
+    json_create_config(l);
+    luaL_setfuncs(l, reg, 1);
 
     /* Set cjson.null */
     lua_pushlightuserdata(l, NULL);
     lua_setfield(l, -2, "null");
 
-    /* Set cjson.version */
-    lua_pushliteral(l, VERSION);
-    lua_setfield(l, -2, "version");
+    /* Set module name / version fields */
+    lua_pushliteral(l, CJSON_MODNAME);
+    lua_setfield(l, -2, "_NAME");
+    lua_pushliteral(l, CJSON_VERSION);
+    lua_setfield(l, -2, "_VERSION");
+
+    return 1;
+}
+
+/* Return cjson.safe module table */
+static int lua_cjson_safe_new(lua_State *l)
+{
+    const char *func[] = { "decode", "encode", NULL };
+    int i;
+
+    lua_cjson_new(l);
+
+    /* Fix new() method */
+    lua_pushcfunction(l, lua_cjson_safe_new);
+    lua_setfield(l, -2, "new");
+
+    for (i = 0; func[i]; i++) {
+        lua_getfield(l, -1, func[i]);
+        lua_pushcclosure(l, json_protect_conversion, 1);
+        lua_setfield(l, -2, func[i]);
+    }
+
+    return 1;
+}
+
+int luaopen_cjson(lua_State *l)
+{
+    lua_cjson_new(l);
+
+#ifdef ENABLE_CJSON_GLOBAL
+    /* Register a global "cjson" table. */
+    lua_pushvalue(l, -1);
+    lua_setglobal(l, CJSON_MODNAME);
+#endif
 
     /* Return cjson table */
     return 1;
 }
 
+int luaopen_cjson_safe(lua_State *l)
+{
+    lua_cjson_safe_new(l);
+
+    /* Return cjson.safe table */
+    return 1;
+}
+
 /* vi:ai et sw=4 ts=4:
  */