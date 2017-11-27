			if (c->data == NULL)
				ret = PyObject_CallFunction(c->callback, "N",
					cpy_oconfig_to_pyconfig(item, NULL)); /* New reference. */
			else
				ret = PyObject_CallFunction(c->callback, "NO",
					cpy_oconfig_to_pyconfig(item, NULL), c->data); /* New reference. */
			if (ret == NULL)
				cpy_log_exception("loading module");
			else
				Py_DECREF(ret);
		} else {
			WARNING("python plugin: Ignoring unknown config key \"%s\".", item->key);
		}
	}
	return 0;
}

void module_register(void) {
	plugin_register_complex_config("python", cpy_config);
	plugin_register_init("python", cpy_init);
	plugin_register_shutdown("python", cpy_shutdown);
