static void send_unshallow(const struct object_array *shallows)
{
	int i;

	for (i = 0; i < shallows->nr; i++) {
		struct object *object = shallows->objects[i].item;
		if (object->flags & NOT_SHALLOW) {
			struct commit_list *parents;
			packet_write_fmt(1, "unshallow %s",
					 oid_to_hex(&object->oid));
			object->flags &= ~CLIENT_SHALLOW;
			/*
			 * We want to _register_ "object" as shallow, but we
			 * also need to traverse object's parents to deepen a
			 * shallow clone. Unregister it for now so we can
			 * parse and add the parents to the want list, then
			 * re-register it.
			 */
			unregister_shallow(&object->oid);
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
		register_shallow(&object->oid);
	}
}