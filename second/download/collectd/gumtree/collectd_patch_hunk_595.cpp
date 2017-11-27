 		return NULL;
 	}
 	if (meta != NULL && meta != Py_None && !PyDict_Check(meta)) {
 		PyErr_Format(PyExc_TypeError, "meta must be a dict");
 		return NULL;
 	}
-	size = (int) PySequence_Length(values);
+	size = (size_t) PySequence_Length(values);
 	if (size != ds->ds_num) {
-		PyErr_Format(PyExc_RuntimeError, "type %s needs %d values, got %i", value_list.type, ds->ds_num, size);
+		PyErr_Format(PyExc_RuntimeError, "type %s needs %zu values, got %zu", value_list.type, ds->ds_num, size);
 		return NULL;
 	}
-	value = malloc(size * sizeof(*value));
-	for (i = 0; i < size; ++i) {
+	value = calloc(size, sizeof(*value));
+	for (size_t i = 0; i < size; ++i) {
 		PyObject *item, *num;
-		item = PySequence_Fast_GET_ITEM(values, i); /* Borrowed reference. */
+		item = PySequence_Fast_GET_ITEM(values, (int) i); /* Borrowed reference. */
 		switch (ds->ds[i].type) {
 		case DS_TYPE_COUNTER:
 			num = PyNumber_Long(item); /* New reference. */
 			if (num != NULL) {
 				value[i].counter = PyLong_AsUnsignedLongLong(num);
 				Py_XDECREF(num);
