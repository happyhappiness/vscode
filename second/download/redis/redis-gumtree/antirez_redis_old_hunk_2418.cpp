    /* Step 4: generate a new configuration file from the modified state
     * and write it into the original file. */
    newcontent = rewriteConfigGetContentFromState(state);
    printf("%s\n", newcontent);

    sdsfree(newcontent);
    rewriteConfigReleaseState(state);
    return 0;
}

/*-----------------------------------------------------------------------------
