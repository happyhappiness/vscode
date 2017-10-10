 }
 
 static void add_remote_info_ref(struct remote_ls_ctx *ls)
 {
 	struct strbuf *buf = (struct strbuf *)ls->userData;
 	struct object *o;
-	int len;
-	char *ref_info;
 	struct ref *ref;
 
 	ref = alloc_ref(ls->dentry_name);
 
 	if (http_fetch_ref(repo->url, ref) != 0) {
 		fprintf(stderr,
