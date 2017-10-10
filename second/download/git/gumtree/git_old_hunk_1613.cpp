				describe_object(tag->tagged));
			printf(" (%s) in %s\n", tag->tag,
				describe_object(&tag->object));
		}
	}

	return 0;
}

static int fsck_obj_buffer(const struct object_id *oid, enum object_type type,
			   unsigned long size, void *buffer, int *eaten)
{
	/*
