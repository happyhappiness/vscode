        log_pfn_register(p, "^FB", log_ttfb, 0);
    }

    return OK;
}

static const char *logio_track_ttfb(cmd_parms *cmd, void *in_dir_config, int arg)
{
    logio_dirconf_t *dir_config = in_dir_config;
    dir_config->track_ttfb = arg;
    return NULL;
}
