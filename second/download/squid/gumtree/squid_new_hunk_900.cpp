            }

            /* now remove the service */
            if (DeleteService(schService) == 0)
                fprintf(stderr, "DeleteService failed.\n");
            else
                printf("Service " SQUIDSBUFPH " deleted successfully.\n", SQUIDSBUFPRINT(service_name));

            CloseServiceHandle(schService);
        }

        CloseServiceHandle(schSCManager);
    }
}

void
WIN32_SetServiceCommandLine()
{
    if (service_name.isEmpty())
        service_name = SBuf(APP_SHORTNAME);

    const char *service = service_name.c_str();
    strcat(REGKEY, service);

    keys[4] = const_cast<char*>(service);

    /* Now store the Service Command Line in the registry */
    WIN32_StoreKey(COMMANDLINE, REG_SZ, (unsigned char *) WIN32_Command_Line, strlen(WIN32_Command_Line) + 1);
}

void
