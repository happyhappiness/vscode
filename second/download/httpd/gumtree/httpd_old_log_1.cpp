fprintf(stdout,
                "%d\t%d\t%d\t%d\t%" APR_SSIZE_T_FMT "\t",
                i,
                left(i), right(i), parent(i),
                minchild(q, i));