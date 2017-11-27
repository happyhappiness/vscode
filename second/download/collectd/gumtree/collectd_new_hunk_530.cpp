		cpy_build_name(buf, sizeof(buf), arg, NULL);
		name = buf;
	}
	for (tmp = *list_head; tmp; prev = tmp, tmp = tmp->next)
		if (strcmp(name, tmp->name) == 0)
			break;

	Py_DECREF(arg);
	if (tmp == NULL) {
		PyErr_Format(PyExc_RuntimeError, "Unable to unregister %s callback '%s'.", desc, name);
		return NULL;
	}
	/* Yes, this is actually save. To call this function the caller has to
