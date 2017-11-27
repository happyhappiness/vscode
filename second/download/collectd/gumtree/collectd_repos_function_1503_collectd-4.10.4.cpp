static int cpy_notification_callback(const notification_t *notification, user_data_t *data) {
	cpy_callback_t *c = data->data;
	PyObject *ret, *notify;
	Notification *n;

	CPY_LOCK_THREADS
		notify = Notification_New(); /* New reference. */
		n = (Notification *) notify;
		sstrncpy(n->data.host, notification->host, sizeof(n->data.host));
		sstrncpy(n->data.type, notification->type, sizeof(n->data.type));
		sstrncpy(n->data.type_instance, notification->type_instance, sizeof(n->data.type_instance));
		sstrncpy(n->data.plugin, notification->plugin, sizeof(n->data.plugin));
		sstrncpy(n->data.plugin_instance, notification->plugin_instance, sizeof(n->data.plugin_instance));
		n->data.time = notification->time;
		sstrncpy(n->message, notification->message, sizeof(n->message));
		n->severity = notification->severity;
		ret = PyObject_CallFunctionObjArgs(c->callback, n, c->data, (void *) 0); /* New reference. */
		Py_XDECREF(notify);
		if (ret == NULL) {
			cpy_log_exception("notification callback");
		} else {
			Py_DECREF(ret);
		}
	CPY_RELEASE_THREADS
	return 0;
}