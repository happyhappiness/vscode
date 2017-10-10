				error("failed to read delta base object %s"
				      " at offset %"PRIuMAX" from %s",
				      sha1_to_hex(base_sha1), (uintmax_t)obj_offset,
				      p->pack_name);
				mark_bad_packed_object(p, base_sha1);
				base = read_object(base_sha1, &type, &base_size);
			}
		}

		i = --delta_stack_nr;
		obj_offset = delta_stack[i].obj_offset;
		curpos = delta_stack[i].curpos;
