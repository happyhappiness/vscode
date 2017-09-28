             printf("No entry\n");
         } else {
             printf("ERROR: Out of range index should return NULL, returned offset: %ld\n", p-zl);
             return 1;
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Iterate list from 0 to end:\n");
     {
         zl = createList();
         p = ziplistIndex(zl, 0);
