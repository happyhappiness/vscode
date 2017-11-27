static int cow_simple_read (void)
{
  value_t      values[1];
  value_list_t vl = VALUE_LIST_INIT;
  char        *buffer;
  size_t       buffer_size;
  int          status;
  char        *endptr;
  direct_access_element_t *traverse;

  /* traverse list and check entries */
  for (traverse = direct_list; traverse != NULL; traverse = traverse->next)
  {
      vl.values = values;
      vl.values_len = 1;

      sstrncpy (vl.host, hostname_g, sizeof (vl.host));
      sstrncpy (vl.plugin, "onewire", sizeof (vl.plugin));
      sstrncpy (vl.plugin_instance, traverse->address, sizeof (vl.plugin_instance));

      status = OW_get (traverse->path, &buffer, &buffer_size);
      if (status < 0)
      {
          ERROR ("onewire plugin: OW_get (%s) failed. status = %#x;",
                 traverse->path,
                 status);
          return (-1);
      }
      DEBUG ("onewire plugin: Read onewire device %s as %s", traverse->path, buffer);


      endptr = NULL;
      values[0].gauge = strtod (buffer, &endptr);
      if (endptr == NULL)
      {
          ERROR ("onewire plugin: Buffer is not a number: %s", buffer);
          continue;
      }

      sstrncpy (vl.type, traverse->file, sizeof (vl.type));
      sstrncpy (vl.type_instance, "",   sizeof (""));

      plugin_dispatch_values (&vl);
      free (buffer);
  } /* for (traverse) */

  return 0;
}