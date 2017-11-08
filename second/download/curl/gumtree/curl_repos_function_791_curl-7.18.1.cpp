static bool multi_conn_using(struct Curl_multi *multi,
                             struct SessionHandle *data)
{
  /* any live CLOSEACTION-connections pointing to the give 'data' ? */
  int i;

  for(i=0; i< multi->connc->num; i++) {
    if(multi->connc->connects[i] &&
       (multi->connc->connects[i]->data == data) &&
       multi->connc->connects[i]->protocol & PROT_CLOSEACTION)
      return TRUE;
  }

  return FALSE;
}