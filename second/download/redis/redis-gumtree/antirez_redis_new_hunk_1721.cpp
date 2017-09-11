    argv2[2] = sdscatprintf(sdsempty(),"%d",keys);

    /* Call it */
    return issueCommand(argc+3-got_comma, argv2);
}

/*------------------------------------------------------------------------------
