void
url_rewind(URL_FILE *file)
{
    switch(file->type)
    {
    case CFTYPE_FILE:
        rewind(file->handle.file); /* passthrough */
        break;

    case CFTYPE_CURL:
        /* halt transaction */
        curl_multi_remove_handle(multi_handle, file->handle.curl);

        /* restart */
        curl_multi_add_handle(multi_handle, file->handle.curl);

        /* ditch buffer - write will recreate - resets stream pos*/
        if(file->buffer)
            free(file->buffer);

        file->buffer=NULL;
        file->buffer_pos=0;
        file->buffer_len=0;

        break;

    default: /* unknown or supported type - oh dear */
        break;

    }

}