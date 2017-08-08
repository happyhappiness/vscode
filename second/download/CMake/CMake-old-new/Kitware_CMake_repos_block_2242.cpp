{
      fprintf(stdout, "fakefluid is creating file \"%s\"\n", av[i + 1]);
      FILE* file = fopen(av[i + 1], "w");
      fprintf(file, "// Solaris needs non-empty content so ensure\n"
                    "// we have at least one symbol\n"
                    "int Solaris_requires_a_symbol_here = 0;\n");
      fclose(file);
    }