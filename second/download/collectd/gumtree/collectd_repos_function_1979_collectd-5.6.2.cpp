static PyObject *float_or_none(float number) {
  if (isnan(number)) {
    Py_RETURN_NONE;
  }
  return PyFloat_FromDouble(number);
}