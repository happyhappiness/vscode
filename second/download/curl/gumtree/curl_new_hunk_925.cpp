        /* the '%' thing here will cause the trace get sent to stderr */
        Curl_safefree(global->trace_dump);
        global->trace_dump = strdup("%");
        if(!global->trace_dump)
          return PARAM_NO_MEM;
        if(global->tracetype && (global->tracetype != TRACE_PLAIN))
          warnf(global,
                "-v, --verbose overrides an earlier trace/verbose option\n");
        global->tracetype = TRACE_PLAIN;
      }
      else
        /* verbose is disabled here */
        global->tracetype = TRACE_NONE;
