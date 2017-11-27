static PyObject *cpy_common_repr(PyObject *s) {
	PyObject *ret, *tmp;
	static PyObject *l_type = NULL, *l_type_instance = NULL, *l_plugin = NULL, *l_plugin_instance = NULL;
	static PyObject *l_host = NULL, *l_time = NULL;
	PluginData *self = (PluginData *) s;
	
	if (l_type == NULL)
		l_type = cpy_string_to_unicode_or_bytes("(type=");
	if (l_type_instance == NULL)
		l_type_instance = cpy_string_to_unicode_or_bytes(",type_instance=");
	if (l_plugin == NULL)
		l_plugin = cpy_string_to_unicode_or_bytes(",plugin=");
	if (l_plugin_instance == NULL)
		l_plugin_instance = cpy_string_to_unicode_or_bytes(",plugin_instance=");
	if (l_host == NULL)
		l_host = cpy_string_to_unicode_or_bytes(",host=");
	if (l_time == NULL)
		l_time = cpy_string_to_unicode_or_bytes(",time=");
	
	if (!l_type || !l_type_instance || !l_plugin || !l_plugin_instance || !l_host || !l_time)
		return NULL;
	
	ret = cpy_string_to_unicode_or_bytes(s->ob_type->tp_name);

	CPY_STRCAT(&ret, l_type);
	tmp = cpy_string_to_unicode_or_bytes(self->type);
	CPY_SUBSTITUTE(PyObject_Repr, tmp, tmp);
	CPY_STRCAT_AND_DEL(&ret, tmp);

	if (self->type_instance[0] != 0) {
		CPY_STRCAT(&ret, l_type_instance);
		tmp = cpy_string_to_unicode_or_bytes(self->type_instance);
		CPY_SUBSTITUTE(PyObject_Repr, tmp, tmp);
		CPY_STRCAT_AND_DEL(&ret, tmp);
	}

	if (self->plugin[0] != 0) {
		CPY_STRCAT(&ret, l_plugin);
		tmp = cpy_string_to_unicode_or_bytes(self->plugin);
		CPY_SUBSTITUTE(PyObject_Repr, tmp, tmp);
		CPY_STRCAT_AND_DEL(&ret, tmp);
	}

	if (self->plugin_instance[0] != 0) {
		CPY_STRCAT(&ret, l_plugin_instance);
		tmp = cpy_string_to_unicode_or_bytes(self->plugin_instance);
		CPY_SUBSTITUTE(PyObject_Repr, tmp, tmp);
		CPY_STRCAT_AND_DEL(&ret, tmp);
	}

	if (self->host[0] != 0) {
		CPY_STRCAT(&ret, l_host);
		tmp = cpy_string_to_unicode_or_bytes(self->host);
		CPY_SUBSTITUTE(PyObject_Repr, tmp, tmp);
		CPY_STRCAT_AND_DEL(&ret, tmp);
	}

	if (self->time != 0) {
		CPY_STRCAT(&ret, l_time);
		tmp = PyInt_FromLong(self->time);
		CPY_SUBSTITUTE(PyObject_Repr, tmp, tmp);
		CPY_STRCAT_AND_DEL(&ret, tmp);
	}
	return ret;
}