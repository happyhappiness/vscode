             }
             zl = ziplistDelete(zl,&p);
             p = ziplistPrev(zl,p);
             printf("\n");
         }
         printf("\n");
+        zfree(zl);
     }
 
     printf("Delete inclusive range 0,0:\n");
     {
         zl = createList();
         zl = ziplistDeleteRange(zl, 0, 1);
         ziplistRepr(zl);
+        zfree(zl);
     }
 
     printf("Delete inclusive range 0,1:\n");
     {
         zl = createList();
         zl = ziplistDeleteRange(zl, 0, 2);
         ziplistRepr(zl);
+        zfree(zl);
     }
 
     printf("Delete inclusive range 1,2:\n");
     {
         zl = createList();
         zl = ziplistDeleteRange(zl, 1, 2);
         ziplistRepr(zl);
+        zfree(zl);
     }
 
     printf("Delete with start index out of range:\n");
     {
         zl = createList();
         zl = ziplistDeleteRange(zl, 5, 1);
         ziplistRepr(zl);
+        zfree(zl);
     }
 
     printf("Delete with num overflow:\n");
     {
         zl = createList();
         zl = ziplistDeleteRange(zl, 1, 5);
         ziplistRepr(zl);
+        zfree(zl);
     }
 
     printf("Delete foo while iterating:\n");
     {
         zl = createList();
         p = ziplistIndex(zl,0);
