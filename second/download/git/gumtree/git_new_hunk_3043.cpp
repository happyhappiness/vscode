				get_shallow_commits(&want_obj, depth,
						    SHALLOW, NOT_SHALLOW);
		while (result) {
			struct object *object = &result->item->object;
			if (!(object->flags & (CLIENT_SHALLOW|NOT_SHALLOW))) {
				packet_write(1, "shallow %s",
						oid_to_hex(&object->oid));
				register_shallow(object->oid.hash);
				shallow_nr++;
			}
			result = result->next;
		}
		free_commit_list(backup);
		for (i = 0; i < shallows.nr; i++) {
			struct object *object = shallows.objects[i].item;
			if (object->flags & NOT_SHALLOW) {
				struct commit_list *parents;
				packet_write(1, "unshallow %s",
					oid_to_hex(&object->oid));
				object->flags &= ~CLIENT_SHALLOW;
				/* make sure the real parents are parsed */
				unregister_shallow(object->oid.hash);
				object->parsed = 0;
				parse_commit_or_die((struct commit *)object);
				parents = ((struct commit *)object)->parents;
				while (parents) {
					add_object_array(&parents->item->object,
							NULL, &want_obj);
					parents = parents->next;
				}
				add_object_array(object, NULL, &extra_edge_obj);
			}
			/* make sure commit traversal conforms to client */
			register_shallow(object->oid.hash);
		}
		packet_flush(1);
	} else
		if (shallows.nr > 0) {
			int i;
			for (i = 0; i < shallows.nr; i++)
				register_shallow(shallows.objects[i].item->oid.hash);
		}

	shallow_nr += shallows.nr;
	free(shallows.objects);
}

/* return non-zero if the ref is hidden, otherwise 0 */
static int mark_our_ref(const char *refname, const char *refname_full,
			const struct object_id *oid)
{
	struct object *o = lookup_unknown_object(oid->hash);

	if (ref_is_hidden(refname, refname_full)) {
		o->flags |= HIDDEN_REF;
		return 1;
	}
	o->flags |= OUR_REF;
	return 0;
}

static int check_ref(const char *refname_full, const struct object_id *oid,
		     int flag, void *cb_data)
{
	const char *refname = strip_namespace(refname_full);

	mark_our_ref(refname, refname_full, oid);
	return 0;
}

static void format_symref_info(struct strbuf *buf, struct string_list *symref)
{
	struct string_list_item *item;
