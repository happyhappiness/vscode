 	struct ref_filter *filter = ref_cbdata->filter;
 	struct ref_array_item *ref;
 	struct commit *commit = NULL;
 	unsigned int kind;
 
 	if (flag & REF_BAD_NAME) {
-		warning("ignoring ref with broken name %s", refname);
+		warning(_("ignoring ref with broken name %s"), refname);
 		return 0;
 	}
 
 	if (flag & REF_ISBROKEN) {
-		warning("ignoring broken ref %s", refname);
+		warning(_("ignoring broken ref %s"), refname);
 		return 0;
 	}
 
 	/* Obtain the current ref kind from filter_ref_kind() and ignore unwanted refs. */
 	kind = filter_ref_kind(filter, refname);
 	if (!(kind & filter->kind))
