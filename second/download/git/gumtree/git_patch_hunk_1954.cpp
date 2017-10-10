 		break;
 
 	case 0:
 		if (type_from_string(exp_type) == OBJ_BLOB) {
 			unsigned char blob_sha1[20];
 			if (sha1_object_info(sha1, NULL) == OBJ_TAG) {
-				enum object_type type;
-				unsigned long size;
 				char *buffer = read_sha1_file(sha1, &type, &size);
 				const char *target;
 				if (!skip_prefix(buffer, "object ", &target) ||
 				    get_sha1_hex(target, blob_sha1))
 					die("%s not a valid tag", sha1_to_hex(sha1));
 				free(buffer);
