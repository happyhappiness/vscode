    }



  fprintf(fout,"\nstatic PyMethodDef Py%s_ClassMethods[] = {\n",

	  kitName);

  fprintf(fout,"{NULL, NULL, 0, NULL}};\n\n");

  

#ifdef _WIN32

