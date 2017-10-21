     tag_table = (int *)malloc(sizeof(tag_table[0])*TABLESIZE);
 
   targets = (struct target *)malloc(sizeof(targets[0])*s->count);
   if (!tag_table || !targets) 
     out_of_memory("build_hash_table");
 
-  for (i=0;i<s->count;i++) {
+  for (i=0;i<(int) s->count;i++) {
     targets[i].i = i;
     targets[i].t = gettag(s->sums[i].sum1);
   }
 
   qsort(targets,s->count,sizeof(targets[0]),(int (*)())compare_targets);
 
