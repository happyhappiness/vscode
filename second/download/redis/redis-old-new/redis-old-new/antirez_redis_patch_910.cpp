@@ -176,6 +176,8 @@ struct redisCommand redisCommandTable[] = {
     {"zrange",zrangeCommand,-4,"r",0,NULL,1,1,1,0,0},
     {"zrangebyscore",zrangebyscoreCommand,-4,"r",0,NULL,1,1,1,0,0},
     {"zrevrangebyscore",zrevrangebyscoreCommand,-4,"r",0,NULL,1,1,1,0,0},
+    {"zrangebylex",zrangebylexCommand,-4,"r",0,NULL,1,1,1,0,0},
+    {"zrevrangebylex",zrevrangebylexCommand,-4,"r",0,NULL,1,1,1,0,0},
     {"zcount",zcountCommand,4,"r",0,NULL,1,1,1,0,0},
     {"zrevrange",zrevrangeCommand,-4,"r",0,NULL,1,1,1,0,0},
     {"zcard",zcardCommand,2,"r",0,NULL,1,1,1,0,0},
@@ -1346,6 +1348,12 @@ void createSharedObjects(void) {
         shared.bulkhdr[j] = createObject(REDIS_STRING,
             sdscatprintf(sdsempty(),"$%d\r\n",j));
     }
+    /* The following two shared objects, minstring and maxstrings, are not
+     * actually used for their value but as a special object meaning
+     * respectively the minimum possible string and the maximum possible
+     * string in string comparisons for the ZRANGEBYLEX command. */
+    shared.minstring = createStringObject("minstring",9);
+    shared.maxstring = createStringObject("maxstring",9);
 }
 
 void initServerConfig() {