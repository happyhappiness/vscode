 						PyDict_SetItemString(dict, table[i], Py_False);
 				}
 				free(table[i]);
 			}
 			free(table);
 		}
-		val = Values_New(); /* New reference. */
-		v = (Values *) val; 
+		v = (Values *) Values_New(); /* New reference. */
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
-		v->meta = dict;
+		v->meta = dict;  /* Steals a reference. */
 		ret = PyObject_CallFunctionObjArgs(c->callback, v, c->data, (void *) 0); /* New reference. */
-		Py_XDECREF(val);
+		Py_XDECREF(v);
 		if (ret == NULL) {
 			cpy_log_exception("write callback");
 		} else {
 			Py_DECREF(ret);
 		}
 	CPY_RELEASE_THREADS
