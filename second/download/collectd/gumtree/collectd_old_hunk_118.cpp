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
