 				if (lstat(ce->name, &sb))
 					die(_("could not stat file '%s'"), ce->name);
 				if (!(st.st_mode & S_IFDIR))
 					unlink_or_warn(ce->name);
 
 				return submodule_move_head(ce->name,
-					NULL, oid_to_hex(&ce->oid),
-					SUBMODULE_MOVE_HEAD_FORCE);
+					NULL, oid_to_hex(&ce->oid), 0);
 			} else
 				return submodule_move_head(ce->name,
 					"HEAD", oid_to_hex(&ce->oid),
-					SUBMODULE_MOVE_HEAD_FORCE);
+					state->force ? SUBMODULE_MOVE_HEAD_FORCE : 0);
 		}
 
 		if (!changed)
 			return 0;
 		if (!state->force) {
 			if (!state->quiet)
