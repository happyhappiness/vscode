@@ -2153,6 +2153,8 @@ ldbLog(sdsnew("[b]reak -<line>      Remove breakpoint from the specified line.")
 ldbLog(sdsnew("[b]reak 0            Remove all breakpoints."));
 ldbLog(sdsnew("[e]eval <code>       Execute some Lua code (in a different callframe)."));
 ldbLog(sdsnew("[r]edis <cmd>        Execute a Redis command."));
+ldbLog(sdsnew("[a]abort             Stop the execution of the script. In sync"));
+ldbLog(sdsnew("                     mode dataset changes will be retained."));
 ldbLog(sdsnew(""));
 ldbLog(sdsnew("Debugger functions you can call from Lua scripts:"));
 ldbLog(sdsnew("redis.debug()        Produce logs in the debugger console."));
@@ -2171,6 +2173,9 @@ ldbLog(sdsnew("                     in the next line of code."));
         } else if (!strcasecmp(argv[0],"e") || !strcasecmp(argv[0],"eval")) {
             ldbEval(lua,argv,argc);
             ldbSendLogs();
+        } else if (!strcasecmp(argv[0],"a") || !strcasecmp(argv[0],"abort")) {
+            lua_pushstring(lua, "script aborted for user request");
+            lua_error(lua);
         } else if (argc > 1 &&
                    (!strcasecmp(argv[0],"r") || !strcasecmp(argv[0],"redis"))) {
             ldbRedis(lua,argv,argc);