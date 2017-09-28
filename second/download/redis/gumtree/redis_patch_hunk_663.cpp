 
             p = ziplistIndex(zl,-i-1);
             assert(ziplistGet(p,NULL,NULL,&value));
             assert(999-i == value);
         }
         printf("SUCCESS\n\n");
+        zfree(zl);
     }
 
     printf("Compare strings with ziplist entries:\n");
     {
         zl = createList();
         p = ziplistIndex(zl,0);
