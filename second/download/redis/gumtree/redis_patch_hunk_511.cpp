         is = intsetAdd(is,4,&success); assert(success);
         is = intsetAdd(is,4,&success); assert(!success);
         ok();
     }
 
     printf("Large number of random adds: "); {
-        int inserts = 0;
+        uint32_t inserts = 0;
         is = intsetNew();
         for (i = 0; i < 1024; i++) {
             is = intsetAdd(is,rand()%0x800,&success);
             if (success) inserts++;
         }
         assert(intrev32ifbe(is->length) == inserts);
