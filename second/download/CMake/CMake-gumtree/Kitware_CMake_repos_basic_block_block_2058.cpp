{
      FILE* file = Fopen(filename, "a+b");
      if (file) {
        fclose(file);
        return true;
      }
      return false;
    }