 	return 0;
 }
 
 static int cpy_write_callback(const data_set_t *ds, const value_list_t *value_list, user_data_t *data) {
 	int i;
 	cpy_callback_t *c = data->data;
-	PyObject *ret, *v, *list;
+	PyObject *ret, *list, *temp, *dict = NULL;
+	Values *v;
 
 	CPY_LOCK_THREADS
 		list = PyList_New(value_list->values_len); /* New reference. */
 		if (list == NULL) {
 			cpy_log_exception("write callback");
 			CPY_RETURN_FROM_THREADS 0;
 		}
 		for (i = 0; i < value_list->values_len; ++i) {
-			if (ds->ds[i].type == DS_TYPE_COUNTER) {
+			if (ds->ds->type == DS_TYPE_COUNTER) {
 				if ((long) value_list->values[i].counter == value_list->values[i].counter)
 					PyList_SetItem(list, i, PyInt_FromLong(value_list->values[i].counter));
 				else
 					PyList_SetItem(list, i, PyLong_FromUnsignedLongLong(value_list->values[i].counter));
-			} else if (ds->ds[i].type == DS_TYPE_GAUGE) {
+			} else if (ds->ds->type == DS_TYPE_GAUGE) {
 				PyList_SetItem(list, i, PyFloat_FromDouble(value_list->values[i].gauge));
-			} else if (ds->ds[i].type == DS_TYPE_DERIVE) {
+			} else if (ds->ds->type == DS_TYPE_DERIVE) {
 				if ((long) value_list->values[i].derive == value_list->values[i].derive)
 					PyList_SetItem(list, i, PyInt_FromLong(value_list->values[i].derive));
 				else
 					PyList_SetItem(list, i, PyLong_FromLongLong(value_list->values[i].derive));
-			} else if (ds->ds[i].type == DS_TYPE_ABSOLUTE) {
+			} else if (ds->ds->type == DS_TYPE_ABSOLUTE) {
 				if ((long) value_list->values[i].absolute == value_list->values[i].absolute)
 					PyList_SetItem(list, i, PyInt_FromLong(value_list->values[i].absolute));
 				else
 					PyList_SetItem(list, i, PyLong_FromUnsignedLongLong(value_list->values[i].absolute));
 			} else {
 				Py_BEGIN_ALLOW_THREADS
-				ERROR("cpy_write_callback: Unknown value type %d.", ds->ds[i].type);
+				ERROR("cpy_write_callback: Unknown value type %d.", ds->ds->type);
 				Py_END_ALLOW_THREADS
 				Py_DECREF(list);
 				CPY_RETURN_FROM_THREADS 0;
 			}
 			if (PyErr_Occurred() != NULL) {
 				cpy_log_exception("value building for write callback");
-				Py_DECREF(list);
 				CPY_RETURN_FROM_THREADS 0;
 			}
 		}
-		v = PyObject_CallFunction((void *) &ValuesType, "sOssssdi", value_list->type,
-				list, value_list->plugin_instance, value_list->type_instance,
-				value_list->plugin, value_list->host, (double) value_list->time,
-				value_list->interval); /* New reference. */
-		Py_DECREF(list);
+		dict = PyDict_New();
+		if (value_list->meta) {
+			int i, num;
+			char **table;
+			meta_data_t *meta = value_list->meta;
+
+			num = meta_data_toc(meta, &table);
+			for (i = 0; i < num; ++i) {
+				int type;
+				char *string;
+				int64_t si;
+				uint64_t ui;
+				double d;
+				_Bool b;
+				
+				type = meta_data_type(meta, table[i]);
+				if (type == MD_TYPE_STRING) {
+					if (meta_data_get_string(meta, table[i], &string))
+						continue;
+					temp = cpy_string_to_unicode_or_bytes(string);
+					free(string);
+					PyDict_SetItemString(dict, table[i], temp);
+					Py_XDECREF(temp);
+				} else if (type == MD_TYPE_SIGNED_INT) {
+					if (meta_data_get_signed_int(meta, table[i], &si))
+						continue;
+					temp = PyObject_CallFunctionObjArgs((void *) &SignedType, PyLong_FromLongLong(si), (void *) 0);
+					PyDict_SetItemString(dict, table[i], temp);
+					Py_XDECREF(temp);
+				} else if (type == MD_TYPE_UNSIGNED_INT) {
+					if (meta_data_get_unsigned_int(meta, table[i], &ui))
+						continue;
+					temp = PyObject_CallFunctionObjArgs((void *) &UnsignedType, PyLong_FromUnsignedLongLong(ui), (void *) 0);
+					PyDict_SetItemString(dict, table[i], temp);
+					Py_XDECREF(temp);
+				} else if (type == MD_TYPE_DOUBLE) {
+					if (meta_data_get_double(meta, table[i], &d))
+						continue;
+					temp = PyFloat_FromDouble(d);
+					PyDict_SetItemString(dict, table[i], temp);
+					Py_XDECREF(temp);
+				} else if (type == MD_TYPE_BOOLEAN) {
+					if (meta_data_get_boolean(meta, table[i], &b))
+						continue;
+					if (b)
+						PyDict_SetItemString(dict, table[i], Py_True);
+					else
+						PyDict_SetItemString(dict, table[i], Py_False);
+				}
+				free(table[i]);
+			}
+			free(table);
+		}
+		v = PyObject_New(Values, (void *) &ValuesType);
+		sstrncpy(v->data.host, value_list->host, sizeof(v->data.host));
+		sstrncpy(v->data.type, value_list->type, sizeof(v->data.type));
+		sstrncpy(v->data.type_instance, value_list->type_instance, sizeof(v->data.type_instance));
+		sstrncpy(v->data.plugin, value_list->plugin, sizeof(v->data.plugin));
+		sstrncpy(v->data.plugin_instance, value_list->plugin_instance, sizeof(v->data.plugin_instance));
+		v->data.time = value_list->time;
+		v->interval = value_list->interval;
+		v->values = list;
+		v->meta = dict;
 		ret = PyObject_CallFunctionObjArgs(c->callback, v, c->data, (void *) 0); /* New reference. */
-		Py_XDECREF(v);
 		if (ret == NULL) {
 			cpy_log_exception("write callback");
 		} else {
 			Py_DECREF(ret);
 		}
 	CPY_RELEASE_THREADS
 	return 0;
 }
 
 static int cpy_notification_callback(const notification_t *notification, user_data_t *data) {
 	cpy_callback_t *c = data->data;
-	PyObject *ret, *n;
+	PyObject *ret;
+	Notification *n;
 
 	CPY_LOCK_THREADS
-		n = PyObject_CallFunction((void *) &NotificationType, "ssssssdi", notification->type, notification->message,
-				notification->plugin_instance, notification->type_instance, notification->plugin,
-				notification->host, (double) notification->time, notification->severity); /* New reference. */
+		n = PyObject_New(Notification, (void *) &NotificationType);
+		sstrncpy(n->data.host, notification->host, sizeof(n->data.host));
+		sstrncpy(n->data.type, notification->type, sizeof(n->data.type));
+		sstrncpy(n->data.type_instance, notification->type_instance, sizeof(n->data.type_instance));
+		sstrncpy(n->data.plugin, notification->plugin, sizeof(n->data.plugin));
+		sstrncpy(n->data.plugin_instance, notification->plugin_instance, sizeof(n->data.plugin_instance));
+		n->data.time = notification->time;
+		sstrncpy(n->message, notification->message, sizeof(n->message));
+		n->severity = notification->severity;
 		ret = PyObject_CallFunctionObjArgs(c->callback, n, c->data, (void *) 0); /* New reference. */
-		Py_XDECREF(n);
 		if (ret == NULL) {
 			cpy_log_exception("notification callback");
 		} else {
 			Py_DECREF(ret);
 		}
 	CPY_RELEASE_THREADS
 	return 0;
 }
 
 static void cpy_log_callback(int severity, const char *message, user_data_t *data) {
 	cpy_callback_t * c = data->data;
-	PyObject *ret;
+	PyObject *ret, *text;
 
 	CPY_LOCK_THREADS
+	text = cpy_string_to_unicode_or_bytes(message);
 	if (c->data == NULL)
-		ret = PyObject_CallFunction(c->callback, "is", severity, message); /* New reference. */
+		ret = PyObject_CallFunction(c->callback, "iN", severity, text); /* New reference. */
 	else
-		ret = PyObject_CallFunction(c->callback, "isO", severity, message, c->data); /* New reference. */
+		ret = PyObject_CallFunction(c->callback, "iNO", severity, text, c->data); /* New reference. */
 
 	if (ret == NULL) {
 		/* FIXME */
 		/* Do we really want to trigger a log callback because a log callback failed?
 		 * Probably not. */
 		PyErr_Print();
