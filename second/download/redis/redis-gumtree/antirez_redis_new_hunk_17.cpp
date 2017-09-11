                printf("Successfully truncated AOF\n");
            }
        } else {
            printf("AOF is not valid. "
                   "Use the --fix option to try fixing it.\n");
            exit(1);
        }
    } else {
