 	klen = kstar - key;
 	ksuffixlen = strlen(kstar + 1);
 	namelen = strlen(name);
 	ret = !strncmp(name, key, klen) && namelen >= klen + ksuffixlen &&
 		!memcmp(name + namelen - ksuffixlen, kstar + 1, ksuffixlen);
 	if (ret && value) {
+		struct strbuf sb = STRBUF_INIT;
 		const char *vstar = strchr(value, '*');
-		size_t vlen;
-		size_t vsuffixlen;
 		if (!vstar)
 			die("Value '%s' of pattern has no '*'", value);
-		vlen = vstar - value;
-		vsuffixlen = strlen(vstar + 1);
-		*result = xmalloc(vlen + vsuffixlen +
-				  strlen(name) -
-				  klen - ksuffixlen + 1);
-		strncpy(*result, value, vlen);
-		strncpy(*result + vlen,
-			name + klen, namelen - klen - ksuffixlen);
-		strcpy(*result + vlen + namelen - klen - ksuffixlen,
-		       vstar + 1);
+		strbuf_add(&sb, value, vstar - value);
+		strbuf_add(&sb, name + klen, namelen - klen - ksuffixlen);
+		strbuf_addstr(&sb, vstar + 1);
+		*result = strbuf_detach(&sb, NULL);
 	}
 	return ret;
 }
 
 static void query_refspecs_multiple(struct refspec *refs, int ref_count, struct refspec *query, struct string_list *results)
 {
