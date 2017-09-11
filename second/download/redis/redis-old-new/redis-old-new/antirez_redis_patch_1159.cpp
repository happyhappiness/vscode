@@ -1,5 +1,5 @@
 /*
-** $Id: lvm.c,v 2.63.1.3 2007/12/28 15:32:23 roberto Exp $
+** $Id: lvm.c,v 2.63.1.5 2011/08/17 20:43:11 roberto Exp $
 ** Lua virtual machine
 ** See Copyright Notice in lua.h
 */
@@ -133,6 +133,7 @@ void luaV_gettable (lua_State *L, const TValue *t, TValue *key, StkId val) {
 
 void luaV_settable (lua_State *L, const TValue *t, TValue *key, StkId val) {
   int loop;
+  TValue temp;
   for (loop = 0; loop < MAXTAGLOOP; loop++) {
     const TValue *tm;
     if (ttistable(t)) {  /* `t' is a table? */
@@ -141,6 +142,7 @@ void luaV_settable (lua_State *L, const TValue *t, TValue *key, StkId val) {
       if (!ttisnil(oldval) ||  /* result is no nil? */
           (tm = fasttm(L, h->metatable, TM_NEWINDEX)) == NULL) { /* or no TM? */
         setobj2t(L, oldval, val);
+        h->flags = 0;
         luaC_barriert(L, h, val);
         return;
       }
@@ -152,7 +154,9 @@ void luaV_settable (lua_State *L, const TValue *t, TValue *key, StkId val) {
       callTM(L, tm, t, key, val);
       return;
     }
-    t = tm;  /* else repeat with `tm' */ 
+    /* else repeat with `tm' */
+    setobj(L, &temp, tm);  /* avoid pointing inside table (may rehash) */
+    t = &temp;
   }
   luaG_runerror(L, "loop in settable");
 }