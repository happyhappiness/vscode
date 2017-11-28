
            if (!ConfigFile)
                ConfigFile = xstrdup(DefaultConfigFile);

            WIN32_StoreKey(CONFIGFILE, REG_SZ, (unsigned char *) ConfigFile, strlen(ConfigFile) + 1);

            printf("Squid Cache version %s for %s\n", version_string,
                   CONFIG_HOST_TYPE);

            printf("installed successfully as %s Windows System Service.\n",
                   WIN32_Service_name);

            printf
            ("To run, start it from the Services Applet of Control Panel.\n");

            printf("Don't forget to edit squid.conf before starting it.\n\n");
        } else {
            fprintf(stderr, "CreateService failed\n");
            exit(1);
        }

