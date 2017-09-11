@@ -1,18 +1,7 @@
-
-#include <assert.h>
-#include <ctype.h>
-#include <limits.h>
-#include <string.h>
-
-
-#include "lua.h"
-#include "lauxlib.h"
-
-
 /*
 ** {======================================================
 ** Library for packing/unpacking structures.
-** $Id: struct.c,v 1.2 2008/04/18 20:06:01 roberto Exp $
+** $Id: struct.c,v 1.4 2012/07/04 18:54:29 roberto Exp $
 ** See Copyright Notice at the end of this file
 ** =======================================================
 */
@@ -25,6 +14,7 @@
 ** b/B - signed/unsigned byte
 ** h/H - signed/unsigned short
 ** l/L - signed/unsigned long
+** T   - size_t
 ** i/In - signed/unsigned integer with size `n' (default is size of int)
 ** cn - sequence of `n' chars (from/to a string); when packing, n==0 means
         the whole string; when unpacking, n==0 means use the previous
@@ -36,6 +26,38 @@
 */
 
 
+#include <assert.h>
+#include <ctype.h>
+#include <limits.h>
+#include <stddef.h>
+#include <string.h>
+
+
+#include "lua.h"
+#include "lauxlib.h"
+
+
+#if (LUA_VERSION_NUM >= 502)
+
+#define luaL_register(L,n,f)	luaL_newlib(L,f)
+
+#endif
+
+
+/* basic integer type */
+#if !defined(STRUCT_INT)
+#define STRUCT_INT	long
+#endif
+
+typedef STRUCT_INT Inttype;
+
+/* corresponding unsigned version */
+typedef unsigned STRUCT_INT Uinttype;
+
+
+/* maximum size (in bytes) for integral types */
+#define MAXINTSIZE	32
+
 /* is 'x' a power of 2? */
 #define isp2(x)		((x) > 0 && ((x) & ((x) - 1)) == 0)
 
@@ -67,11 +89,11 @@ typedef struct Header {
 } Header;
 
 
-static size_t getnum (const char **fmt, size_t df) {
+static int getnum (const char **fmt, int df) {
   if (!isdigit(**fmt))  /* no number? */
     return df;  /* return default value */
   else {
-    size_t a = 0;
+    int a = 0;
     do {
       a = a*10 + *((*fmt)++) - '0';
     } while (isdigit(**fmt));
@@ -89,33 +111,40 @@ static size_t optsize (lua_State *L, char opt, const char **fmt) {
     case 'B': case 'b': return sizeof(char);
     case 'H': case 'h': return sizeof(short);
     case 'L': case 'l': return sizeof(long);
+    case 'T': return sizeof(size_t);
     case 'f':  return sizeof(float);
     case 'd':  return sizeof(double);
     case 'x': return 1;
     case 'c': return getnum(fmt, 1);
-    case 's': case ' ': case '<': case '>': case '!': return 0;
     case 'i': case 'I': {
       int sz = getnum(fmt, sizeof(int));
-      if (!isp2(sz))
-        luaL_error(L, "integral size %d is not a power of 2", sz);
+      if (sz > MAXINTSIZE)
+        luaL_error(L, "integral size %d is larger than limit of %d",
+                       sz, MAXINTSIZE);
       return sz;
     }
-    default: {
-      const char *msg = lua_pushfstring(L, "invalid format option [%c]", opt);
-      return luaL_argerror(L, 1, msg);
-    }
+    default: return 0;  /* other cases do not need alignment */
   }
 }
 
 
+/*
+** return number of bytes needed to align an element of size 'size'
+** at current position 'len'
+*/
 static int gettoalign (size_t len, Header *h, int opt, size_t size) {
   if (size == 0 || opt == 'c') return 0;
-  if (size > (size_t)h->align) size = h->align;  /* respect max. alignment */
-  return  (size - (len & (size - 1))) & (size - 1);
+  if (size > (size_t)h->align)
+    size = h->align;  /* respect max. alignment */
+  return (size - (len & (size - 1))) & (size - 1);
 }
 
 
-static void commoncases (lua_State *L, int opt, const char **fmt, Header *h) {
+/*
+** options to control endianess and alignment
+*/
+static void controloptions (lua_State *L, int opt, const char **fmt,
+                            Header *h) {
   switch (opt) {
     case  ' ': return;  /* ignore white spaces */
     case '>': h->endian = BIG; return;
@@ -127,29 +156,38 @@ static void commoncases (lua_State *L, int opt, const char **fmt, Header *h) {
       h->align = a;
       return;
     }
-    default: assert(0);
+    default: {
+      const char *msg = lua_pushfstring(L, "invalid format option '%c'", opt);
+      luaL_argerror(L, 1, msg);
+    }
   }
 }
 
 
 static void putinteger (lua_State *L, luaL_Buffer *b, int arg, int endian,
                         int size) {
   lua_Number n = luaL_checknumber(L, arg);
-  unsigned long value;
-  if (n < (lua_Number)LONG_MAX)
-    value = (long)n;
+  Uinttype value;
+  char buff[MAXINTSIZE];
+  if (n < 0)
+    value = (Uinttype)(Inttype)n;
   else
-    value = (unsigned long)n;
+    value = (Uinttype)n;
   if (endian == LITTLE) {
     int i;
-    for (i = 0; i < size; i++)
-      luaL_addchar(b, (value >> 8*i) & 0xff);
+    for (i = 0; i < size; i++) {
+      buff[i] = (value & 0xff);
+      value >>= 8;
+    }
   }
   else {
     int i;
-    for (i = size - 1; i >= 0; i--)
-      luaL_addchar(b, (value >> 8*i) & 0xff);
+    for (i = size - 1; i >= 0; i--) {
+      buff[i] = (value & 0xff);
+      value >>= 8;
+    }
   }
+  luaL_addlstring(b, buff, size);
 }
 
 
@@ -179,15 +217,15 @@ static int b_pack (lua_State *L) {
     size_t size = optsize(L, opt, &fmt);
     int toalign = gettoalign(totalsize, &h, opt, size);
     totalsize += toalign;
-    while (toalign-- > 0) luaL_putchar(&b, '\0');
+    while (toalign-- > 0) luaL_addchar(&b, '\0');
     switch (opt) {
       case 'b': case 'B': case 'h': case 'H':
-      case 'l': case 'L': case 'i': case 'I': {  /* integer types */
+      case 'l': case 'L': case 'T': case 'i': case 'I': {  /* integer types */
         putinteger(L, &b, arg++, h.endian, size);
         break;
       }
       case 'x': {
-        luaL_putchar(&b, '\0');
+        luaL_addchar(&b, '\0');
         break;
       }
       case 'f': {
@@ -209,12 +247,12 @@ static int b_pack (lua_State *L) {
         luaL_argcheck(L, l >= (size_t)size, arg, "string too short");
         luaL_addlstring(&b, s, size);
         if (opt == 's') {
-          luaL_putchar(&b, '\0');  /* add zero at the end */
+          luaL_addchar(&b, '\0');  /* add zero at the end */
           size++;
         }
         break;
       }
-      default: commoncases(L, opt, &fmt, &h);
+      default: controloptions(L, opt, &fmt, &h);
     }
     totalsize += size;
   }
@@ -225,24 +263,27 @@ static int b_pack (lua_State *L) {
 
 static lua_Number getinteger (const char *buff, int endian,
                         int issigned, int size) {
-  unsigned long l = 0;
+  Uinttype l = 0;
+  int i;
   if (endian == BIG) {
-    int i;
-    for (i = 0; i < size; i++)
-      l |= (unsigned long)(unsigned char)buff[size - i - 1] << (i*8);
+    for (i = 0; i < size; i++) {
+      l <<= 8;
+      l |= (Uinttype)(unsigned char)buff[i];
+    }
   }
   else {
-    int i;
-    for (i = 0; i < size; i++)
-      l |= (unsigned long)(unsigned char)buff[i] << (i*8);
+    for (i = size - 1; i >= 0; i--) {
+      l <<= 8;
+      l |= (Uinttype)(unsigned char)buff[i];
+    }
   }
   if (!issigned)
     return (lua_Number)l;
   else {  /* signed format */
-    unsigned long mask = ~(0UL) << (size*8 - 1);
+    Uinttype mask = (Uinttype)(~((Uinttype)0)) << (size*8 - 1);
     if (l & mask)  /* negative value? */
       l |= mask;  /* signal extension */
-    return (lua_Number)(long)l;
+    return (lua_Number)(Inttype)l;
   }
 }
 
@@ -260,9 +301,10 @@ static int b_unpack (lua_State *L) {
     size_t size = optsize(L, opt, &fmt);
     pos += gettoalign(pos, &h, opt, size);
     luaL_argcheck(L, pos+size <= ld, 2, "data string too short");
+    luaL_checkstack(L, 1, "too many results");
     switch (opt) {
       case 'b': case 'B': case 'h': case 'H':
-      case 'l': case 'L': case 'i':  case 'I': {  /* integer types */
+      case 'l': case 'L': case 'T': case 'i':  case 'I': {  /* integer types */
         int issigned = islower(opt);
         lua_Number res = getinteger(data+pos, h.endian, issigned, size);
         lua_pushnumber(L, res);
@@ -304,34 +346,58 @@ static int b_unpack (lua_State *L) {
         lua_pushlstring(L, data+pos, size - 1);
         break;
       }
-      default: commoncases(L, opt, &fmt, &h);
+      default: controloptions(L, opt, &fmt, &h);
     }
     pos += size;
   }
   lua_pushinteger(L, pos + 1);
   return lua_gettop(L) - 2;
 }
 
+
+static int b_size (lua_State *L) {
+  Header h;
+  const char *fmt = luaL_checkstring(L, 1);
+  size_t pos = 0;
+  defaultoptions(&h);
+  while (*fmt) {
+    int opt = *fmt++;
+    size_t size = optsize(L, opt, &fmt);
+    pos += gettoalign(pos, &h, opt, size);
+    if (opt == 's')
+      luaL_argerror(L, 1, "option 's' has no fixed size");
+    else if (opt == 'c' && size == 0)
+      luaL_argerror(L, 1, "option 'c0' has no fixed size");
+    if (!isalnum(opt))
+      controloptions(L, opt, &fmt, &h);
+    pos += size;
+  }
+  lua_pushinteger(L, pos);
+  return 1;
+}
+
 /* }====================================================== */
 
 
 
-static const struct luaL_reg thislib[] = {
+static const struct luaL_Reg thislib[] = {
   {"pack", b_pack},
   {"unpack", b_unpack},
+  {"size", b_size},
   {NULL, NULL}
 };
 
 
+LUALIB_API int luaopen_struct (lua_State *L);
+
 LUALIB_API int luaopen_struct (lua_State *L) {
   luaL_register(L, "struct", thislib);
   return 1;
 }
 
 
-
 /******************************************************************************
-* Copyright (C) 2010 Lua.org, PUC-Rio.  All rights reserved.
+* Copyright (C) 2010-2012 Lua.org, PUC-Rio.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
@@ -352,3 +418,4 @@ LUALIB_API int luaopen_struct (lua_State *L) {
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 ******************************************************************************/
+