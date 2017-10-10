 	int num = 0, size = 50;
 	long cur = 0;
 	unsigned long *ends = NULL;
 	char *data = NULL;
 
 	if (diff_populate_filespec(spec, 0))
-		die("Cannot read blob %s", sha1_to_hex(spec->sha1));
+		die("Cannot read blob %s", oid_to_hex(&spec->oid));
 
 	ALLOC_ARRAY(ends, size);
 	ends[cur++] = 0;
 	data = spec->data;
 	while (num < spec->size) {
 		if (data[num] == '\n' || num == spec->size - 1) {
