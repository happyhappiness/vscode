          warnf(operation, "%s:%d: warning: '%s' uses unquoted white space in"
                " the line that may cause side-effects!\n",
                filename, lineno, option);
        }
      }

      if(!*param) {
        /* do this so getparameter can check for required parameters.
           Otherwise it always thinks there's a parameter. */
        if(alloced_param)
          Curl_safefree(param);
        param = NULL;
      }
