PyMODINIT_FUNC PyInit_collectd(void) {
	return PyModule_Create(&collectdmodule);
}