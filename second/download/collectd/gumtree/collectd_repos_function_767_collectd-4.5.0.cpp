static int parse_ds (data_source_t *dsrc, char *buf, size_t buf_len)
{
  char *dummy;
  char *saveptr;
  char *fields[8];
  int   fields_num;

  if (buf_len < 11)
  {
    ERROR ("parse_ds: (buf_len = %zu) < 11", buf_len);
    return (-1);
  }

  if (buf[buf_len - 1] == ',')
  {
    buf_len--;
    buf[buf_len] = '\0';
  }

  dummy = buf;
  saveptr = NULL;

  fields_num = 0;
  while (fields_num < 8)
  {
    if ((fields[fields_num] = strtok_r (dummy, ":", &saveptr)) == NULL)
      break;
    dummy = NULL;
    fields_num++;
  }

  if (fields_num != 4)
  {
    ERROR ("parse_ds: (fields_num = %i) != 4", fields_num);
    return (-1);
  }

  sstrncpy (dsrc->name, fields[0], sizeof (dsrc->name));

  if (strcasecmp (fields[1], "GAUGE") == 0)
    dsrc->type = DS_TYPE_GAUGE;
  else if (strcasecmp (fields[1], "COUNTER") == 0)
    dsrc->type = DS_TYPE_COUNTER;
  else
  {
    ERROR ("(fields[1] = %s) != (GAUGE || COUNTER)", fields[1]);
    return (-1);
  }

  if (strcasecmp (fields[2], "U") == 0)
    dsrc->min = NAN;
  else
    dsrc->min = atof (fields[2]);

  if (strcasecmp (fields[3], "U") == 0)
    dsrc->max = NAN;
  else
    dsrc->max = atof (fields[3]);

  return (0);
}