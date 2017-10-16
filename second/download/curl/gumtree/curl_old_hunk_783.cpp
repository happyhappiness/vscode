      }
      else {
        param = line; /* parameter starts here */
        while(*line && !ISSPACE(*line))
          line++;
        *line = '\0'; /* zero terminate */
      }

      if(param && !*param) {
        /* do this so getparameter can check for required parameters.
           Otherwise it always thinks there's a parameter. */
        if(alloced_param)
