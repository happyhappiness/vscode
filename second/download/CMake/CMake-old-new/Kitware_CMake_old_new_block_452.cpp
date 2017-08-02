{
      format_ptr = get_netscape_format(co);
      if(format_ptr == NULL) {
        fprintf(out, "#\n# Fatal libcurl error\n");
        if(!use_stdout)
          fclose(out);
        return 1;
      }
      fprintf(out, "%s\n", format_ptr);
      free(format_ptr);
      co=co->next;
    }