void Curl_easy_addmulti(struct SessionHandle *data,
                        void *multi)
{
  data->multi = multi;
  if(multi == NULL)
    /* the association is cleared, mark the easy handle as not used by an
       interface */
    data->state.used_interface = Curl_if_none;
}