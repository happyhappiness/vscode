			 * buf is deleted by the caller.
			 */
			obj = parse_object_buffer(sha1, type, size, buf, &eaten);
			if (!obj)
				die(_("invalid %s"), typename(type));
			if (do_fsck_object &&
			    fsck_object(obj, 1, fsck_error_function))
				die(_("Error in object"));
			if (fsck_walk(obj, mark_link, NULL))
				die(_("Not all child objects of %s are reachable"), sha1_to_hex(obj->sha1));

			if (obj->type == OBJ_TREE) {
				struct tree *item = (struct tree *) obj;
