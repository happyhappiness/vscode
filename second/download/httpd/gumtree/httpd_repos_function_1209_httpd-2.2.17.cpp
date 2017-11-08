static void clean_var_rec(var_rec *mime_info)
{
    mime_info->sub_req = NULL;
    mime_info->mime_type = "";
    mime_info->file_name = "";
    mime_info->body = 0;
    mime_info->content_encoding = NULL;
    mime_info->content_languages = NULL;
    mime_info->content_charset = "";
    mime_info->description = "";

    mime_info->is_pseudo_html = 0;
    mime_info->level = 0.0f;
    mime_info->level_matched = 0.0f;
    mime_info->bytes = -1;
    mime_info->lang_index = -1;
    mime_info->mime_stars = 0;
    mime_info->definite = 1;

    mime_info->charset_quality = 1.0f;
    mime_info->encoding_quality = 1.0f;
    mime_info->lang_quality = 1.0f;
    mime_info->mime_type_quality = 1.0f;
    mime_info->source_quality = 0.0f;
}