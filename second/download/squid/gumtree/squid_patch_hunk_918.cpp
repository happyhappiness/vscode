     if ((hid = hash_create((HASHCMP *) strcmp, 229, hash4)) < 0) {
         printf("hash_create error.\n");
         exit(1);
     }
     printf("done creating hash table: %d\n", hid);
 
+    std::mt19937 mt;
+    xuniform_int_distribution<> dist(0,16);
+
     while (fgets(buf, BUFSIZ, stdin)) {
         buf[strlen(buf) - 1] = '\0';
         printf("Inserting '%s' for item %p to hash table: %d\n",
                buf, buf, hid);
         hash_insert(hid, xstrdup(buf), (void *) 0x12345678);
-        if (random() % 17 == 0)
+        if (dist(mt) == 0)
             strcpy(todelete, buf);
     }
 
     printf("walking hash table...\n");
     for (int i = 0, walker = hash_first(hid); walker; walker = hash_next(hid)) {
         printf("item %5d: key: '%s' item: %p\n", i++, walker->key,
