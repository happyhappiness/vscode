static PyObject *Config_repr(PyObject *s) {
  Config *self = (Config *)s;
  PyObject *ret = NULL;
  static PyObject *node_prefix = NULL, *root_prefix = NULL, *ending = NULL;

  /* This is ok because we have the GIL, so this is thread-save by default. */
  if (node_prefix == NULL)
    node_prefix = cpy_string_to_unicode_or_bytes("<collectd.Config node ");
  if (root_prefix == NULL)
    root_prefix = cpy_string_to_unicode_or_bytes("<collectd.Config root node ");
  if (ending == NULL)
    ending = cpy_string_to_unicode_or_bytes(">");
  if (node_prefix == NULL || root_prefix == NULL || ending == NULL)
    return NULL;

  ret = PyObject_Str(self->key);
  CPY_SUBSTITUTE(PyObject_Repr, ret, ret);
  if (self->parent == NULL || self->parent == Py_None)
    CPY_STRCAT(&ret, root_prefix);
  else
    CPY_STRCAT(&ret, node_prefix);
  CPY_STRCAT(&ret, ending);

  return ret;
}