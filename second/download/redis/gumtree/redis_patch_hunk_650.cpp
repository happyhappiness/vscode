             if (elen && fwrite(entry,elen,1,stdout) == 0) perror("fwrite");
             printf("\n");
         } else {
             printf("%lld\n", value);
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Get element at index 4 (out of range):\n");
     {
         zl = createList();
         p = ziplistIndex(zl, 4);
