static void
Curl_formadd_release_local(struct curl_forms * forms, int nargs, int skip)

{
  while(nargs--)
    if(nargs != skip)
      if(Curl_is_formadd_string(forms[nargs].option))
        if(forms[nargs].value)
          free((char *) forms[nargs].value);

  free((char *) forms);
}