            if (context->err == REDIS_ERR_EOF)
                return REDIS_ERR;
        }
        cliPrintContextErrorAndExit();
        return REDIS_ERR; /* avoid compiler warning */
    }

