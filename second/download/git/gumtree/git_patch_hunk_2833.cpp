 			if (!obj)
 				die(_("invalid %s"), typename(type));
 			if (do_fsck_object &&
 			    fsck_object(obj, buf, size, &fsck_options))
 				die(_("Error in object"));
 			if (fsck_walk(obj, NULL, &fsck_options))
-				die(_("Not all child objects of %s are reachable"), sha1_to_hex(obj->sha1));
+				die(_("Not all child objects of %s are reachable"), oid_to_hex(&obj->oid));
 
 			if (obj->type == OBJ_TREE) {
 				struct tree *item = (struct tree *) obj;
 				item->buffer = NULL;
 				obj->parsed = 0;
 			}
