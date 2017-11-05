static void stats (FILE *output)
{
    int i;
    char *ipstring;
    struct nsrec *current;
    char *errstring[MAX_ERR + 3];

    for (i = 0; i < MAX_ERR + 3; i++)
        errstring[i] = "Unknown error";
    errstring[HOST_NOT_FOUND] = "Host not found";
    errstring[TRY_AGAIN] = "Try again";
    errstring[NO_RECOVERY] = "Non recoverable error";
    errstring[NO_DATA] = "No data record";
    errstring[NO_ADDRESS] = "No address";
    errstring[NO_REVERSE] = "No reverse entry";

    fprintf(output, "logresolve Statistics:\n");

    fprintf(output, "Entries: %d\n", entries);
    fprintf(output, "    With name   : %d\n", withname);
    fprintf(output, "    Resolves    : %d\n", resolves);
    if (errors[HOST_NOT_FOUND])
        fprintf(output, "    - Not found : %d\n", errors[HOST_NOT_FOUND]);
    if (errors[TRY_AGAIN])
        fprintf(output, "    - Try again : %d\n", errors[TRY_AGAIN]);
    if (errors[NO_DATA])
        fprintf(output, "    - No data   : %d\n", errors[NO_DATA]);
    if (errors[NO_ADDRESS])
        fprintf(output, "    - No address: %d\n", errors[NO_ADDRESS]);
    if (errors[NO_REVERSE])
        fprintf(output, "    - No reverse: %d\n", errors[NO_REVERSE]);
    fprintf(output, "Cache hits      : %d\n", cachehits);
    fprintf(output, "Cache size      : %d\n", cachesize);
    fprintf(output, "Cache buckets   :     IP number * hostname\n");

    for (i = 0; i < BUCKETS; i++)
        for (current = nscache[i]; current != NULL; current = current->next) {
            ipstring = inet_ntoa(current->ipnum);
            if (current->noname == 0)
                fprintf(output, "  %3d  %15s - %s\n", i, ipstring,
                        current->hostname);
            else {
                if (current->noname > MAX_ERR + 2)
                    fprintf(output, "  %3d  %15s : Unknown error\n", i,
                            ipstring);
                else
                    fprintf(output, "  %3d  %15s : %s\n", i, ipstring,
                            errstring[current->noname]);
            }
        }
}