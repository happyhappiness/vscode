static PyObject *sys_path, *cpy_format_exception;

static cpy_callback_t *cpy_config_callbacks;
static cpy_callback_t *cpy_init_callbacks;
static cpy_callback_t *cpy_shutdown_callbacks;

/* Make sure to hold the GIL while modifying these. */
static int cpy_shutdown_triggered = 0;
static int cpy_num_callbacks = 0;

static void cpy_destroy_user_data(void *data) {
	cpy_callback_t *c = data;
	free(c->name);
	CPY_LOCK_THREADS
	Py_DECREF(c->callback);
	Py_XDECREF(c->data);
	free(c);
	--cpy_num_callbacks;
	if (!cpy_num_callbacks && cpy_shutdown_triggered) {
		Py_Finalize();
		return;
	}
	CPY_RELEASE_THREADS
}

/* You must hold the GIL to call this function!
 * But if you managed to extract the callback parameter then you probably already do. */

static void cpy_build_name(char *buf, size_t size, PyObject *callback, const char *name) {
	const char *module = NULL;
	PyObject *mod = NULL;

	if (name != NULL) {
		snprintf(buf, size, "python.%s", name);
		return;
	}

	mod = PyObject_GetAttrString(callback, "__module__"); /* New reference. */
	if (mod != NULL)
		module = cpy_unicode_or_bytes_to_string(&mod);

	if (module != NULL) {
		snprintf(buf, size, "python.%s", module);
		Py_XDECREF(mod);
		PyErr_Clear();
		return;
	}
	Py_XDECREF(mod);

	snprintf(buf, size, "python.%p", callback);
	PyErr_Clear();
}

void cpy_log_exception(const char *context) {
	int l = 0;
	const char *typename = NULL, *message = NULL;
	PyObject *type, *value, *traceback, *tn, *m, *list;

	PyErr_Fetch(&type, &value, &traceback);
	PyErr_NormalizeException(&type, &value, &traceback);
	if (type == NULL) return;
	tn = PyObject_GetAttrString(type, "__name__"); /* New reference. */
	m = PyObject_Str(value); /* New reference. */
	if (tn != NULL)
