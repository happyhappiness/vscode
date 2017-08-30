          kitName);

  

  fprintf(fout,"  d = PyModule_GetDict(m);\n");

  fprintf(fout,"  if (!d) Py_FatalError(\"can't get dictionary for module %s!\");\n\n",

          kitName);



  for (i = 0; i < classes.size(); i++)

    {

    fprintf(fout,"  if ((c = PyVTKClass_%sNew(modulename)))\n",

            classes[i].c_str());

    fprintf(fout,"    if (-1 == PyDict_SetItemString(d, \"%s\", c))\n",

            classes[i].c_str());

    fprintf(fout,"      Py_FatalError(\"can't add class %s to dictionary!\");\n\n",

            classes[i].c_str());

    }

  fprintf(fout,"}\n\n");
