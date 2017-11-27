static void parse_range(char *string, range_t *range) {
  char *min_ptr;
  char *max_ptr;

  if (*string == '@') {
    range->invert = 1;
    string++;
  }

  max_ptr = strchr(string, ':');
  if (max_ptr == NULL) {
    min_ptr = NULL;
    max_ptr = string;
  } else {
    min_ptr = string;
    *max_ptr = '\0';
    max_ptr++;
  }

  assert(max_ptr != NULL);

  /* `10' == `0:10' */
  if (min_ptr == NULL)
    range->min = 0.0;
  /* :10 == ~:10 == -inf:10 */
  else if ((*min_ptr == '\0') || (*min_ptr == '~'))
    range->min = NAN;
  else
    range->min = atof(min_ptr);

  if ((*max_ptr == '\0') || (*max_ptr == '~'))
    range->max = NAN;
  else
    range->max = atof(max_ptr);
}