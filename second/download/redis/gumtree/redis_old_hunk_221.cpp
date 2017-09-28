    if (config.dbnum != 0 && config.last_cmd_type != REDIS_REPLY_ERROR)
        len += snprintf(config.prompt+len,sizeof(config.prompt)-len,"[%d]",
            config.dbnum);
    snprintf(config.prompt+len,sizeof(config.prompt)-len,"> ");
}

/*------------------------------------------------------------------------------
 * Help functions
 *--------------------------------------------------------------------------- */

#define CLI_HELP_COMMAND 1
#define CLI_HELP_GROUP 2
