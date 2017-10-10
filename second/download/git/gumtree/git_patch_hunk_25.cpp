 				struct tree *item = (struct tree *) obj;
 				item->buffer = NULL;
 				obj->parsed = 0;
 			}
 			if (obj->type == OBJ_COMMIT) {
 				struct commit *commit = (struct commit *) obj;
-				commit->buffer = NULL;
+				if (detach_commit_buffer(commit, NULL) != data)
+					die("BUG: parse_object_buffer transmogrified our buffer");
 			}
 			obj->flags |= FLAG_CHECKED;
 		}
 		read_unlock();
 	}
 
