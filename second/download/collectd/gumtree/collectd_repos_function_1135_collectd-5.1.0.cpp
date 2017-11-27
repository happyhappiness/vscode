static int nginx_read (void)
{
  int i;

  char *ptr;
  char *lines[16];
  int   lines_num = 0;
  char *saveptr;

  char *fields[16];
  int   fields_num;

  if (curl == NULL)
    return (-1);
  if (url == NULL)
    return (-1);

  nginx_buffer_len = 0;
  if (curl_easy_perform (curl) != 0)
  {
    WARNING ("nginx plugin: curl_easy_perform failed: %s", nginx_curl_error);
    return (-1);
  }

  ptr = nginx_buffer;
  saveptr = NULL;
  while ((lines[lines_num] = strtok_r (ptr, "\n\r", &saveptr)) != NULL)
  {
    ptr = NULL;
    lines_num++;

    if (lines_num >= 16)
      break;
  }

  /*
   * Active connections: 291
   * server accepts handled requests
   *  16630948 16630948 31070465
   * Reading: 6 Writing: 179 Waiting: 106
   */
  for (i = 0; i < lines_num; i++)
  {
    fields_num = strsplit (lines[i], fields,
	(sizeof (fields) / sizeof (fields[0])));

    if (fields_num == 3)
    {
      if ((strcmp (fields[0], "Active") == 0)
	  && (strcmp (fields[1], "connections:") == 0))
      {
	submit ("nginx_connections", "active", atoll (fields[2]));
      }
      else if ((atoll (fields[0]) != 0)
	  && (atoll (fields[1]) != 0)
	  && (atoll (fields[2]) != 0))
      {
	submit ("nginx_requests", NULL, atoll (fields[2]));
      }
    }
    else if (fields_num == 6)
    {
      if ((strcmp (fields[0], "Reading:") == 0)
	  && (strcmp (fields[2], "Writing:") == 0)
	  && (strcmp (fields[4], "Waiting:") == 0))
      {
	submit ("nginx_connections", "reading", atoll (fields[1]));
	submit ("nginx_connections", "writing", atoll (fields[3]));
	submit ("nginx_connections", "waiting", atoll (fields[5]));
      }
    }
  }

  nginx_buffer_len = 0;

  return (0);
}