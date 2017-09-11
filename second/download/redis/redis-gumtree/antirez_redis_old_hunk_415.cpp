                break;
        }
        if (i != helpEntriesLen) continue;
        printf("%s\n", cmdname);

        helpEntriesLen++;
        helpEntries = zrealloc(helpEntries,sizeof(helpEntry)*helpEntriesLen);
