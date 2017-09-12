
    /* Finally create the object from the serialized dump and
     * store it at the specified key. */
    o = rdbLoadObject(data[0],fp);
    if (o == NULL) {
        addReplyError(c,"Bad data format.");
        fclose(fp);
        return;
