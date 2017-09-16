		expansion = in - 1;

		if (*in == '{') {

		    ++in;

		    start_of_var_name = in;

		    in = strchr(in, '}');

		    if (in == NULL) {

                        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR,

				    r, "Missing '}' on variable \"%s\"",

				    expansion);

                        *next = '\0';

                        return;

                    }

		    end_of_var_name = in;

		    ++in;

