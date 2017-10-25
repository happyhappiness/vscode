static FormInfo * AddFormInfo(char *value,
                              char *contenttype,
                              FormInfo *parent_form_info)
{
  FormInfo *form_info;
  form_info = (FormInfo *)malloc(sizeof(FormInfo));
  if(form_info) {
    memset(form_info, 0, sizeof(FormInfo));
    if (value)
      form_info->value = value;
    if (contenttype)
      form_info->contenttype = contenttype;
    form_info->flags = HTTPPOST_FILENAME;
  }
  else
    return NULL;

  if (parent_form_info) {
    /* now, point our 'more' to the original 'more' */
    form_info->more = parent_form_info->more;

    /* then move the original 'more' to point to ourselves */
    parent_form_info->more = form_info;
  }
  else
    return NULL;

  return form_info;
}