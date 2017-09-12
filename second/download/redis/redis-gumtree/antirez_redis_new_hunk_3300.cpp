
    /* Finally create the object from the serialized dump and
     * store it at the specified key. */
    if ((data[0] > 4 && data[0] < 9) ||
         data[0] > 11 ||
        (o = rdbLoadObject(data[0],fp)) == NULL)
    {
        addReplyError(c,"Bad data format.");
        fclose(fp);
        return;
