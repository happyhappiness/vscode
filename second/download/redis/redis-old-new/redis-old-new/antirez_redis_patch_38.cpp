@@ -1029,8 +1029,6 @@ void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
     /* Log INFO and CLIENT LIST */
     serverLogRaw(LL_WARNING|LL_RAW, "\n------ INFO OUTPUT ------\n");
     infostring = genRedisInfoString("all");
-    infostring = sdscatprintf(infostring, "hash_init_value: %u\n",
-        dictGetHashFunctionSeed());
     serverLogRaw(LL_WARNING|LL_RAW, infostring);
     serverLogRaw(LL_WARNING|LL_RAW, "\n------ CLIENT LIST OUTPUT ------\n");
     clients = getAllClientsInfoString();