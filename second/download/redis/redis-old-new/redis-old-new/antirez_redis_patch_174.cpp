@@ -75,7 +75,7 @@ void show_entry(long pos, struct entry *e) {
     if (pos >= 15 && pos <= 19) tag = "new accessed ";
     if (pos >= keyspace_size -5) tag= "old no access";
 
-    printf("%ld] <%s> frequency:%d decrtime:%d [%lu hits | age:%ld seconds]\n",
+    printf("%ld] <%s> frequency:%d decrtime:%d [%lu hits | age:%ld sec]\n",
         pos, tag, e->counter, e->decrtime, (unsigned long)e->hits,
             time(NULL) - e->ctime);
 }
@@ -134,7 +134,7 @@ int main(void) {
 
         /* Simulate the addition of new entries at positions between
          * 10 and 19, a random one every 10 seconds. */
-        if (new_entry_time == now) {
+        if (new_entry_time <= now) {
             idx = 10+(rand()%10);
             entries[idx].counter = COUNTER_INIT_VAL;
             entries[idx].decrtime = to_16bit_minutes(start);