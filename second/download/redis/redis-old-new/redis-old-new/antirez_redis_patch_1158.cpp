@@ -1,5 +1,5 @@
 /*
-** $Id: lstrlib.c,v 1.132.1.4 2008/07/11 17:27:21 roberto Exp $
+** $Id: lstrlib.c,v 1.132.1.5 2010/05/14 15:34:19 roberto Exp $
 ** Standard library for string operations and pattern-matching
 ** See Copyright Notice in lua.h
 */
@@ -754,6 +754,7 @@ static void addintlen (char *form) {
 
 
 static int str_format (lua_State *L) {
+  int top = lua_gettop(L);
   int arg = 1;
   size_t sfl;
   const char *strfrmt = luaL_checklstring(L, arg, &sfl);
@@ -768,7 +769,8 @@ static int str_format (lua_State *L) {
     else { /* format item */
       char form[MAX_FORMAT];  /* to store the format (`%...') */
       char buff[MAX_ITEM];  /* to store the formatted item */
-      arg++;
+      if (++arg > top)
+        luaL_argerror(L, arg, "no value");
       strfrmt = scanformat(L, strfrmt, form);
       switch (*strfrmt++) {
         case 'c': {