{
    fprintf(ofp, "  if(fwrite(kwsysEncodedArray%s_%d, 1,\n"
                 "            sizeof(kwsysEncodedArray%s_%d), ofp) !=\n"
                 "       sizeof(kwsysEncodedArray%s_%d))\n",
            argv[4], i, argv[4], i, argv[4], i);
    fprintf(ofp, "    {\n");
    fprintf(ofp, "    fclose(ofp);\n");
    fprintf(ofp, "    _unlink(fname);\n");
    fprintf(ofp, "    return 0;\n");
    fprintf(ofp, "    }\n");
    }