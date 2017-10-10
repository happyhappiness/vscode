 		return 0;
 	if (data->flags & SEEN_ONLY) {
 		struct commit *c = lookup_commit(graft->oid.hash);
 		if (!c || !(c->object.flags & SEEN)) {
 			if (data->flags & VERBOSE)
 				printf("Removing %s from .git/shallow\n",
-				       sha1_to_hex(c->object.sha1));
+				       oid_to_hex(&c->object.oid));
 			return 0;
 		}
 	}
 	data->count++;
 	if (data->use_pack_protocol)
 		packet_buf_write(data->out, "shallow %s", hex);
