            argv[4], i, argv[4], i, argv[4], i);
    fprintf(ofp, "    {\n");
    fprintf(ofp, "    fclose(ofp);\n");
    fprintf(ofp, "    kwsys_unlink(fname);\n");
    fprintf(ofp, "    return 0;\n");
    fprintf(ofp, "    }\n");
    }