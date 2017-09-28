                 printf("%lld", value);
             }
             p = ziplistNext(zl,p);
             printf("\n");
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Iterate list from 2 to end:\n");
     {
         zl = createList();
         p = ziplistIndex(zl, 2);
