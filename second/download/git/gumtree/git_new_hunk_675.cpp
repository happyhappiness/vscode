	}

	if (obj->type == OBJ_TAG) {
		struct tag *tag = (struct tag *) obj;

		if (show_tags && tag->tagged) {
			printf("tagged %s %s", printable_type(tag->tagged),
				describe_object(tag->tagged));
			printf(" (%s) in %s\n", tag->tag,
				describe_object(&tag->object));
		}
	}

	return 0;
}

static int fsck_obj_buffer(const unsigned char *sha1, enum object_type type,
			   unsigned long size, void *buffer, int *eaten)
{
	/*
	 * Note, buffer may be NULL if type is OBJ_BLOB. See
	 * verify_packfile(), data_valid variable for details.
