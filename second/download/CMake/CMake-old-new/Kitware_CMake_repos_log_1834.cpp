fprintf(out, "#\n# Fatal libcurl error\n");
      if(!use_stdout)
        fclose(out);
      return 1;
    }
    fpr