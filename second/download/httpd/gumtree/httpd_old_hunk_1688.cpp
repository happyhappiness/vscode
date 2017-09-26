
      if (*code == OP_XCLASS)
        {
        int ch;
        while ((ch = *ccode++) != XCL_END)
          {
          if (ch == XCL_PROP)
            {
            fprintf(f, "\\p{%s}", get_ucpname(*ccode++));
            }
          else if (ch == XCL_NOTPROP)
            {
            fprintf(f, "\\P{%s}", get_ucpname(*ccode++));
            }
          else
            {
            ccode += 1 + print_char(f, ccode, TRUE);
            if (ch == XCL_RANGE)
              {
              fprintf(f, "-");
              ccode += 1 + print_char(f, ccode, TRUE);
