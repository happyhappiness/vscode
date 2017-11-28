            // extract base directory
            line[ subs[offset].rm_eo ] = '\0';
            if ( debug ) fprintf( debug, "# match from %d-%d on \"%s\"\n",
                                      (int)subs[offset].rm_so,
                                      (int)subs[offset].rm_eo,
                                      line+subs[offset].rm_so );
            cd.base = xstrdup( line+subs[offset].rm_so );
            ++offset;

            // extract size information
            line[ subs[offset].rm_eo ] = '\0';
            if ( debug ) fprintf( debug, "# match from %d-%d on \"%s\"\n",
                                      (int)subs[offset].rm_so,
