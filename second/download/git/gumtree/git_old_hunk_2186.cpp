#include "revision.h"
#include "list-objects.h"

static void process_blob(struct rev_info *revs,
			 struct blob *blob,
			 show_object_fn show,
			 struct name_path *path,
			 const char *name,
			 void *cb_data)
{
	struct object *obj = &blob->object;

	if (!revs->blob_objects)
		return;
	if (!obj)
		die("bad blob object");
	if (obj->flags & (UNINTERESTING | SEEN))
		return;
	obj->flags |= SEEN;
	show(obj, path, name, cb_data);
}

/*
 * Processing a gitlink entry currently does nothing, since
 * we do not recurse into the subproject.
 *
