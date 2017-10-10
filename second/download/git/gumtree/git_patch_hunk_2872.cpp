 	int i;
 
 	printf("* %d-way merge\n", o->merge_size);
 	debug_stage("index", stages[0], o);
 	for (i = 1; i <= o->merge_size; i++) {
 		char buf[24];
-		sprintf(buf, "ent#%d", i);
+		xsnprintf(buf, sizeof(buf), "ent#%d", i);
 		debug_stage(buf, stages[i], o);
 	}
 	return 0;
 }
 
 static struct lock_file lock_file;
