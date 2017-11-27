						PyDict_SetItemString(dict, table[i], Py_False);
				}
				free(table[i]);
			}
			free(table);
		}
		val = Values_New(); /* New reference. */
		v = (Values *) val; 
		sstrncpy(v->data.host, value_list->host, sizeof(v->data.host));
		sstrncpy(v->data.type, value_list->type, sizeof(v->data.type));
		sstrncpy(v->data.type_instance, value_list->type_instance, sizeof(v->data.type_instance));
		sstrncpy(v->data.plugin, value_list->plugin, sizeof(v->data.plugin));
		sstrncpy(v->data.plugin_instance, value_list->plugin_instance, sizeof(v->data.plugin_instance));
		v->data.time = value_list->time;
		v->interval = value_list->interval;
		Py_CLEAR(v->values);
		v->values = list;
		Py_CLEAR(v->meta);
		v->meta = dict;
		ret = PyObject_CallFunctionObjArgs(c->callback, v, c->data, (void *) 0); /* New reference. */
		Py_XDECREF(val);
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
