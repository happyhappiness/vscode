         */
        new->real = r;
    }
    new->fake = f;
    new->handler = cmd->info;

    return NULL;
}

static const char *add_alias(cmd_parms *cmd, void *dummy, const char *f,
                             const char *r)
{
