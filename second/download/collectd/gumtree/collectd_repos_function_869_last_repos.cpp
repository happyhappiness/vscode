static PyObject *Notification_repr(PyObject *s) {
  PyObject *ret, *tmp;
  static PyObject *l_severity = NULL, *l_message = NULL, *l_meta = NULL,
                  *l_closing = NULL;
  Notification *self = (Notification *)s;

  if (l_severity == NULL)
    l_severity = cpy_string_to_unicode_or_bytes(",severity=");
  if (l_message == NULL)
    l_message = cpy_string_to_unicode_or_bytes(",message=");
  if (l_meta == NULL)
    l_meta = cpy_string_to_unicode_or_bytes(",meta=");
  if (l_closing == NULL)
    l_closing = cpy_string_to_unicode_or_bytes(")");

  if (l_severity == NULL || l_message == NULL || l_meta == NULL ||
      l_closing == NULL)
    return NULL;

  ret = cpy_common_repr(s);
  if (self->severity != 0) {
    CPY_STRCAT(&ret, l_severity);
    tmp = PyInt_FromLong(self->severity);
    CPY_SUBSTITUTE(PyObject_Repr, tmp, tmp);
    CPY_STRCAT_AND_DEL(&ret, tmp);
  }
  if (self->message[0] != 0) {
    CPY_STRCAT(&ret, l_message);
    tmp = cpy_string_to_unicode_or_bytes(self->message);
    CPY_SUBSTITUTE(PyObject_Repr, tmp, tmp);
    CPY_STRCAT_AND_DEL(&ret, tmp);
  }
  if (self->meta &&
      (!PyDict_Check(self->meta) || PyDict_Size(self->meta) > 0)) {
    CPY_STRCAT(&ret, l_meta);
    tmp = PyObject_Repr(self->meta);
    CPY_STRCAT_AND_DEL(&ret, tmp);
  }
  CPY_STRCAT(&ret, l_closing);
  return ret;
}