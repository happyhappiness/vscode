 	if (ret != NULL)
 		return ret;
 	PyErr_Clear();
 	return PyBytes_FromString(buf);
 #else
 	return PyString_FromString(buf);
-#endif	
+#endif
 }
 
 void cpy_log_exception(const char *context);
 
 /* Python object declarations. */
 
