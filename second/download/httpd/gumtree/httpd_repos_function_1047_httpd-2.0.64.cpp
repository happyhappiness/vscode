static void set_mime_fields(var_rec *var, accept_rec *mime_info)
{
    var->mime_type = mime_info->name;
    var->source_quality = mime_info->quality;
    var->level = mime_info->level;
    var->content_charset = mime_info->charset;

    var->is_pseudo_html = (!strcmp(var->mime_type, "text/html")
                           || !strcmp(var->mime_type, INCLUDES_MAGIC_TYPE)
                           || !strcmp(var->mime_type, INCLUDES_MAGIC_TYPE3));
}