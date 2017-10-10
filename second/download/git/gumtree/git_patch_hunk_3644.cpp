 
 			/* Error is printed by lookup_object(). */
 			if (!obj)
 				continue;
 
 			obj->used = 1;
+			if (name_objects)
+				add_decoration(fsck_walk_options.object_names,
+					obj, xstrdup(arg));
 			mark_object_reachable(obj);
 			heads++;
 			continue;
 		}
 		error("invalid parameter: expected sha1, got '%s'", arg);
 	}
