  for (i = 0; i < classes.size(); i++)
    {
#ifdef _WIN32
    fprintf(fout,
            "extern  \"C\" {__declspec( dllexport) PyObject *PyVTKClass_%sNew(char *); }\n",classes[i].c_str());
#else
    fprintf(fout,"extern  \"C\" {PyObject *PyVTKClass_%sNew(char *); }\n",
            classes[i].c_str());
#endif
    }

