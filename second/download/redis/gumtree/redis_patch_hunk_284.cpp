             se->argv[j] = createObject(REDIS_STRING,
                 sdscatprintf(sdsempty(),"... (%d more arguments)",
                 argc-slargc+1));
         } else {
             /* Trim too long strings as well... */
             if (argv[j]->type == REDIS_STRING &&
-                argv[j]->encoding == REDIS_ENCODING_RAW &&
+                sdsEncodedObject(argv[j]) &&
                 sdslen(argv[j]->ptr) > SLOWLOG_ENTRY_MAX_STRING)
             {
                 sds s = sdsnewlen(argv[j]->ptr, SLOWLOG_ENTRY_MAX_STRING);
 
                 s = sdscatprintf(s,"... (%lu more bytes)",
                     (unsigned long)
