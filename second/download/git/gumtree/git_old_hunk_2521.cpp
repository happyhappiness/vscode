#define DIRENT_SORT_HINT(de) 0
#else
#define SORT_DIRENT 1
#define DIRENT_SORT_HINT(de) ((de)->d_ino)
#endif

static void objreport(struct object *obj, const char *severity,
                      const char *err, va_list params)
{
	fprintf(stderr, "%s in %s %s: ",
	        severity, typename(obj->type), sha1_to_hex(obj->sha1));
	vfprintf(stderr, err, params);
	fputs("\n", stderr);
}

__attribute__((format (printf, 2, 3)))
static int objerror(struct object *obj, const char *err, ...)
{
	va_list params;
	va_start(params, err);
	errors_found |= ERROR_OBJECT;
	objreport(obj, "error", err, params);
	va_end(params);
	return -1;
}

__attribute__((format (printf, 3, 4)))
static int fsck_error_func(struct object *obj, int type, const char *err, ...)
{
	va_list params;
	va_start(params, err);
	objreport(obj, (type == FSCK_WARN) ? "warning" : "error", err, params);
	va_end(params);
	return (type == FSCK_WARN) ? 0 : 1;
}

static struct object_array pending;

static int mark_object(struct object *obj, int type, void *data)
{
	struct object *parent = data;

	/*
	 * The only case data is NULL or type is OBJ_ANY is when
	 * mark_object_reachable() calls us.  All the callers of
