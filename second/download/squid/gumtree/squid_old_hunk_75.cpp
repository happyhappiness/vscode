        file = strwordtok(NULL, &saveptr);
    }
#endif /* HAVE_GLOB */
    return error_count;
}

static int
parseOneConfigFile(const char *file_name, unsigned int depth)
{
    FILE *fp = NULL;
    const char *orig_cfg_filename = cfg_filename;
    const int orig_config_lineno = config_lineno;
