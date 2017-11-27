static PyObject *sys_path, *cpy_format_exception;

static cpy_callback_t *cpy_config_callbacks;
static cpy_callback_t *cpy_init_callbacks;
static cpy_callback_t *cpy_shutdown_callbacks;

static void cpy_destroy_user_data(void *data) {
	cpy_callback_t *c = data;
	free(c->name);
	Py_DECREF(c->callback);
	Py_XDECREF(c->data);
	free(c);
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
	int l = 0, i;
	const char *typename = NULL, *message = NULL;
	PyObject *type, *value, *traceback, *tn, *m, *list;
	
	PyErr_Fetch(&type, &value, &traceback);
	PyErr_NormalizeException(&type, &value, &traceback);
	if (type == NULL) return;
	tn = PyObject_GetAttrString(type, "__name__"); /* New reference. */
	m = PyObject_Str(value); /* New reference. */
	if (tn != NULL)
