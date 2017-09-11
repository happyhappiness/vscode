    argv2[2] = sdscatprintf(sdsempty(),"%d",keys);

    /* Call it */
    return cliSendCommand(argc+3-got_comma, argv2, config.repeat);
}

/*------------------------------------------------------------------------------
