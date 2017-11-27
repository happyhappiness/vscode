static xmlXPathObjectPtr cx_evaluate_xpath (xmlXPathContextPtr xpath_ctx, /* {{{ */
           xmlChar *expr)
{
  xmlXPathObjectPtr xpath_obj;

  /* XXX: When to free this? */
  xpath_obj = xmlXPathEvalExpression(BAD_CAST expr, xpath_ctx);
  if (xpath_obj == NULL)
  {
     WARNING ("curl_xml plugin: "
               "Error unable to evaluate xpath expression \"%s\". Skipping...", expr);
     return NULL;
  }

  return xpath_obj;
}