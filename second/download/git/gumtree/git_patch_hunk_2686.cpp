 		size = 0;
 	src.size = size;
 	dst.ptr = result(entry, &size);
 	if (!dst.ptr)
 		size = 0;
 	dst.size = size;
-	xdi_diff(&src, &dst, &xpp, &xecfg, &ecb);
+	if (xdi_diff(&src, &dst, &xpp, &xecfg, &ecb))
+		die("unable to generate diff");
 	free(src.ptr);
 	free(dst.ptr);
 }
 
 static void show_result_list(struct merge_list *entry)
 {
