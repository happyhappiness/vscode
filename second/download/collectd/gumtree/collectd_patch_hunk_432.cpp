 	const data_set_t *ds;
 	int size;
 	value_t *value;
 	value_list_t value_list = VALUE_LIST_INIT;
 	PyObject *values = self->values, *meta = self->meta;
 	double time = self->data.time, interval = self->interval;
-	char *host = NULL, *plugin = NULL, *plugin_instance = NULL, *type = NULL, *type_instance = NULL, *dest = NULL;
+	const char *host = self->data.host;
+	const char *plugin = self->data.plugin;
+	const char *plugin_instance = self->data.plugin_instance;
+	const char *type = self->data.type;
+	const char *type_instance = self->data.type_instance;
+	const char *dest = NULL;
 	
 	static char *kwlist[] = {"destination", "type", "values", "plugin_instance", "type_instance",
 			"plugin", "host", "time", "interval", "meta", NULL};
-	if (!PyArg_ParseTupleAndKeywords(args, kwds, "et|etOetetetetdiO", kwlist, NULL, &dest,
+	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|etOetetetetddO", kwlist,
 			NULL, &type, &values, NULL, &plugin_instance, NULL, &type_instance,
 			NULL, &plugin, NULL, &host, &time, &interval, &meta))
 		return NULL;
 
-	sstrncpy(value_list.host, host ? host : self->data.host, sizeof(value_list.host));
-	sstrncpy(value_list.plugin, plugin ? plugin : self->data.plugin, sizeof(value_list.plugin));
-	sstrncpy(value_list.plugin_instance, plugin_instance ? plugin_instance : self->data.plugin_instance, sizeof(value_list.plugin_instance));
-	sstrncpy(value_list.type, type ? type : self->data.type, sizeof(value_list.type));
-	sstrncpy(value_list.type_instance, type_instance ? type_instance : self->data.type_instance, sizeof(value_list.type_instance));
-	FreeAll();
-	if (value_list.type[0] == 0) {
+	if (type[0] == 0) {
 		PyErr_SetString(PyExc_RuntimeError, "type not set");
 		return NULL;
 	}
-	ds = plugin_get_ds(value_list.type);
+	ds = plugin_get_ds(type);
 	if (ds == NULL) {
-		PyErr_Format(PyExc_TypeError, "Dataset %s not found", value_list.type);
+		PyErr_Format(PyExc_TypeError, "Dataset %s not found", type);
 		return NULL;
 	}
 	if (values == NULL || (PyTuple_Check(values) == 0 && PyList_Check(values) == 0)) {
 		PyErr_Format(PyExc_TypeError, "values must be list or tuple");
 		return NULL;
 	}
 	size = (int) PySequence_Length(values);
 	if (size != ds->ds_num) {
-		PyErr_Format(PyExc_RuntimeError, "type %s needs %d values, got %i", value_list.type, ds->ds_num, size);
+		PyErr_Format(PyExc_RuntimeError, "type %s needs %d values, got %i", type, ds->ds_num, size);
 		return NULL;
 	}
 	value = malloc(size * sizeof(*value));
 	for (i = 0; i < size; ++i) {
 		PyObject *item, *num;
 		item = PySequence_Fast_GET_ITEM(values, i); /* Borrowed reference. */
