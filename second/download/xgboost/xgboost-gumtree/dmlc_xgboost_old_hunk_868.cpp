                if( !strcmp("test:data",  name ) )   test_path  = val;
                if( !strcmp("model_in",  name ) )    model_in   = val;
                if( !strcmp("model_dir", name ) )    model_dir_path = val;
                if( !strncmp("eval[",  name, 5 ) ) {
                    char evname[ 256 ];
                    utils::Assert( sscanf( name, "eval[%[^]]", evname ) == 1, "must specify evaluation name for display");
