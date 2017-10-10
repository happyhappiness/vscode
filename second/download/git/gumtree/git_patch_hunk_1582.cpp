 	data->fd = read_bundle_header(transport->url, &data->header);
 	if (data->fd < 0)
 		die ("Could not read bundle '%s'.", transport->url);
 	for (i = 0; i < data->header.references.nr; i++) {
 		struct ref_list_entry *e = data->header.references.list + i;
 		struct ref *ref = alloc_ref(e->name);
-		hashcpy(ref->old_oid.hash, e->sha1);
+		oidcpy(&ref->old_oid, &e->oid);
 		ref->next = result;
 		result = ref;
 	}
 	return result;
 }
 
