static void cx_xpath_free(cx_xpath_t *xpath) /* {{{ */
{
  if (xpath == NULL)
    return;

  sfree(xpath->path);
  sfree(xpath->type);
  sfree(xpath->instance_prefix);
  sfree(xpath->plugin_instance_from);
  sfree(xpath->instance);
  sfree(xpath->values);
  sfree(xpath);
}