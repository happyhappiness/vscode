fprintf(fout, "extern  \"C\" {__declspec( dllexport) "
            "PyObject *PyVTKClass_%sNew(char *); }\n", classes[i].c_str());