    return 0;

eoferr: /* unexpected end of file is handled here with a fatal exit */
    rdbCheckError("Unexpected EOF reading RDB file");
    return 1;
}

