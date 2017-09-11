                if( !strcmp("name_pred",  name ) )   name_pred = val;
                if( !strcmp("dump_stats", name ) )   dump_model_stats = atoi( val );
                if( !strcmp("interact:action",  name ) )  interact_action = val;
                if( !strncmp("eval[",  name, 5 ) ) {
                    char evname[ 256 ];
                    utils::Assert( sscanf( name, "eval[%[^]]", evname ) == 1, "must specify evaluation name for display");
