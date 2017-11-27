 		"similar to Values but has a severity and a message instead of interval\n"
 		"and time.\n"
 		"Notifications can be dispatched at any time and can be received with register_notification.";
 
 static int Notification_init(PyObject *s, PyObject *args, PyObject *kwds) {
 	Notification *self = (Notification *) s;
-	PyObject *tmp;
-	int severity = 0, ret;
+	int severity = 0;
 	double time = 0;
 	const char *message = "";
 	const char *type = "", *plugin_instance = "", *type_instance = "", *plugin = "", *host = "";
 	static char *kwlist[] = {"type", "message", "plugin_instance", "type_instance",
 			"plugin", "host", "time", "severity", NULL};
 	
-	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|ssssssdi", kwlist,
-			&type, &message, &plugin_instance, &type_instance,
-			&plugin, &host, &time, &severity))
+	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|etetetetetetdi", kwlist,
+			NULL, &type, NULL, &message, NULL, &plugin_instance, NULL, &type_instance,
+			NULL, &plugin, NULL, &host, &time, &severity))
 		return -1;
 	
-	tmp = Py_BuildValue("sssssd", type, plugin_instance, type_instance, plugin, host, time);
-	if (tmp == NULL)
-		return -1;
-	ret = PluginDataType.tp_init(s, tmp, NULL);
-	Py_DECREF(tmp);
-	if (ret != 0)
+	if (type[0] != 0 && plugin_get_ds(type) == NULL) {
+		PyErr_Format(PyExc_TypeError, "Dataset %s not found", type);
 		return -1;
-	
+	}
+
+	sstrncpy(self->data.host, host, sizeof(self->data.host));
+	sstrncpy(self->data.plugin, plugin, sizeof(self->data.plugin));
+	sstrncpy(self->data.plugin_instance, plugin_instance, sizeof(self->data.plugin_instance));
+	sstrncpy(self->data.type, type, sizeof(self->data.type));
+	sstrncpy(self->data.type_instance, type_instance, sizeof(self->data.type_instance));
+	self->data.time = time;
+
 	sstrncpy(self->message, message, sizeof(self->message));
 	self->severity = severity;
 	return 0;
 }
 
 static PyObject *Notification_dispatch(Notification *self, PyObject *args, PyObject *kwds) {
