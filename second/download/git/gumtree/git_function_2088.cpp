static void grab_values(struct atom_value *val, int deref, struct object *obj, void *buf, unsigned long sz)
{
	grab_common_values(val, deref, obj, buf, sz);
	switch (obj->type) {
	case OBJ_TAG:
		grab_tag_values(val, deref, obj, buf, sz);
		grab_sub_body_contents(val, deref, obj, buf, sz);
		grab_person("tagger", val, deref, obj, buf, sz);
		break;
	case OBJ_COMMIT:
		grab_commit_values(val, deref, obj, buf, sz);
		grab_sub_body_contents(val, deref, obj, buf, sz);
		grab_person("author", val, deref, obj, buf, sz);
		grab_person("committer", val, deref, obj, buf, sz);
		break;
	case OBJ_TREE:
		/* grab_tree_values(val, deref, obj, buf, sz); */
		break;
	case OBJ_BLOB:
		/* grab_blob_values(val, deref, obj, buf, sz); */
		break;
	default:
		die("Eh?  Object of type %d?", obj->type);
	}
}