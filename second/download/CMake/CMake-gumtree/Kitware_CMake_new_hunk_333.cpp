                             curl_off_t *size,

                             const char *fmt, ...)

{

  char *s;

  CURLcode result;

  va_list ap;

  va_start(ap, fmt);

  s = curl_mvaprintf(fmt, ap);

  va_end(ap);



  if(!s)

    return CURLE_OUT_OF_MEMORY;



  result = AddFormData(formp, FORM_DATAMEM, s, 0, size);

  if(result)

    free(s);



  return result;

}



/*

