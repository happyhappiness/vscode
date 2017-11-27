lt_dlhandle
lt_dlhandle_next (place)
     lt_dlhandle place;
{
  return place ? place->next : handles;
}