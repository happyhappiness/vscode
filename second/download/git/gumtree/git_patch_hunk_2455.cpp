 		const char *file2, const char *label2)
 {
 	xpparam_t xpp;
 	xdemitconf_t xecfg;
 	xdemitcb_t ecb;
 	mmfile_t minus, plus;
+	int ret;
 
 	if (read_mmfile(&minus, file1) || read_mmfile(&plus, file2))
-		return 1;
+		return -1;
 
 	printf("--- a/%s\n+++ b/%s\n", label1, label2);
 	fflush(stdout);
 	memset(&xpp, 0, sizeof(xpp));
 	xpp.flags = 0;
 	memset(&xecfg, 0, sizeof(xecfg));
 	xecfg.ctxlen = 3;
 	ecb.outf = outf;
-	xdi_diff(&minus, &plus, &xpp, &xecfg, &ecb);
+	ret = xdi_diff(&minus, &plus, &xpp, &xecfg, &ecb);
 
 	free(minus.ptr);
 	free(plus.ptr);
-	return 0;
+	return ret;
 }
 
 int cmd_rerere(int argc, const char **argv, const char *prefix)
 {
 	struct string_list merge_rr = STRING_LIST_INIT_DUP;
 	int i, fd, autoupdate = -1, flags = 0;
