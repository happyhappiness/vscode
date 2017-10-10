 	if (collision_test_needed) {
 		void *has_data;
 		enum object_type has_type;
 		unsigned long has_size;
 		read_lock();
 		has_type = sha1_object_info(sha1, &has_size);
+		if (has_type < 0)
+			die(_("cannot read existing object info %s"), sha1_to_hex(sha1));
 		if (has_type != type || has_size != size)
 			die(_("SHA1 COLLISION FOUND WITH %s !"), sha1_to_hex(sha1));
 		has_data = read_sha1_file(sha1, &has_type, &has_size);
 		read_unlock();
 		if (!data)
 			data = new_data = get_data_from_pack(obj_entry);
