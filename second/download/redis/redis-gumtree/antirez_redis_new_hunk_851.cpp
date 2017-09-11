            fp = stdin;
        } else {
            if ((fp = fopen(filename,"r")) == NULL) {
                serverLog(LL_WARNING,
                    "Fatal error, can't open config file '%s'", filename);
                exit(1);
            }
        }
        while(fgets(buf,CONFIG_MAX_LINE+1,fp) != NULL)
            config = sdscat(config,buf);
        if (fp != stdin) fclose(fp);
    }
