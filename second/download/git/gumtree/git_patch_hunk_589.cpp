 			}
 			if (starts_with(line, "--shallow ")) {
 				unsigned char sha1[20];
 				if (get_sha1_hex(line + 10, sha1))
 					die("not an SHA-1 '%s'", line + 10);
 				register_shallow(sha1);
+				use_bitmap_index = 0;
 				continue;
 			}
 			die("not a rev '%s'", line);
 		}
 		if (handle_revision_arg(line, &revs, flags, REVARG_CANNOT_BE_FILENAME))
 			die("bad revision '%s'", line);
