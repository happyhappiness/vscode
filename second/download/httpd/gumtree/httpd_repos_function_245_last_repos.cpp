static dav_error * dav_fs_get_resource(
    request_rec *r,
    const char *root_dir,
    const char *label,
    int use_checked_in,
    dav_resource **result_resource)
{
    dav_resource_private *ctx;
    dav_resource *resource;
    char *s;
    char *filename;
    apr_size_t len;

    /* ### optimize this into a single allocation! */

    /* Create private resource context descriptor */
    ctx = apr_pcalloc(r->pool, sizeof(*ctx));
    ctx->finfo = r->finfo;
    ctx->r = r;

    /* ### this should go away */
    ctx->pool = r->pool;

    /* Preserve case on OSes which fold canonical filenames */
#if 0
    /* ### not available in Apache 2.0 yet */
    filename = r->case_preserved_filename;
#else
    filename = r->filename;
#endif

    /*
    ** If there is anything in the path_info, then this indicates that the
    ** entire path was not used to specify the file/dir. We want to append
    ** it onto the filename so that we get a "valid" pathname for null
    ** resources.
    */
    s = apr_pstrcat(r->pool, filename, r->path_info, NULL);

    /* make sure the pathname does not have a trailing "/" */
    len = strlen(s);
    if (len > 1 && s[len - 1] == '/') {
        s[len - 1] = '\0';
    }
    ctx->pathname = s;

    /* Create resource descriptor */
    resource = apr_pcalloc(r->pool, sizeof(*resource));
    resource->type = DAV_RESOURCE_TYPE_REGULAR;
    resource->info = ctx;
    resource->hooks = &dav_hooks_repository_fs;
    resource->pool = r->pool;

    /* make sure the URI does not have a trailing "/" */
    len = strlen(r->uri);
    if (len > 1 && r->uri[len - 1] == '/') {
        s = apr_pstrmemdup(r->pool, r->uri, len-1);
        resource->uri = s;
    }
    else {
        resource->uri = r->uri;
    }

    if (r->finfo.filetype != APR_NOFILE) {
        resource->exists = 1;
        resource->collection = r->finfo.filetype == APR_DIR;

        /* unused info in the URL will indicate a null resource */

        if (r->path_info != NULL && *r->path_info != '\0') {
            if (resource->collection) {
                /* only a trailing "/" is allowed */
                if (*r->path_info != '/' || r->path_info[1] != '\0') {

                    /*
                    ** This URL/filename represents a locknull resource or
                    ** possibly a destination of a MOVE/COPY
                    */
                    resource->exists = 0;
                    resource->collection = 0;
                }
            }
            else
            {
                /*
                ** The base of the path refers to a file -- nothing should
                ** be in path_info. The resource is simply an error: it
                ** can't be a null or a locknull resource.
                */
                return dav_new_error(r->pool, HTTP_BAD_REQUEST, 0, 0,
                                     "The URL contains extraneous path "
                                     "components. The resource could not "
                                     "be identified.");
            }

            /* retain proper integrity across the structures */
            if (!resource->exists) {
                ctx->finfo.filetype = APR_NOFILE;
            }
        }
    }

    *result_resource = resource;
    return NULL;
}