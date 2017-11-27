 				ERROR("python plugin: Unable to convert \"%s\" to "
 				      "a python object.", dir);
 				free(dir);
 				cpy_log_exception("python initialization");
 				continue;
 			}
-			if (PyList_Append(sys_path, dir_object) != 0) {
-				ERROR("python plugin: Unable to append \"%s\" to "
+			if (PyList_Insert(sys_path, 0, dir_object) != 0) {
+				ERROR("python plugin: Unable to prepend \"%s\" to "
 				      "python module path.", dir);
 				cpy_log_exception("python initialization");
 			}
 			Py_DECREF(dir_object);
 			free(dir);
 		} else if (strcasecmp(item->key, "Import") == 0) {
