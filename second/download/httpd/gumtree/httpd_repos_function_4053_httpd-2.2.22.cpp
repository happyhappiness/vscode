static real_pcre *
try_flipped(const real_pcre *re, real_pcre *internal_re,
  const pcre_study_data *study, pcre_study_data *internal_study)
{
if (byteflip4(re->magic_number) != MAGIC_NUMBER)
  return NULL;

*internal_re = *re;           /* To copy other fields */
internal_re->size = byteflip4(re->size);
internal_re->options = byteflip4(re->options);
internal_re->top_bracket = byteflip2(re->top_bracket);
internal_re->top_backref = byteflip2(re->top_backref);
internal_re->first_byte = byteflip2(re->first_byte);
internal_re->req_byte = byteflip2(re->req_byte);
internal_re->name_table_offset = byteflip2(re->name_table_offset);
internal_re->name_entry_size = byteflip2(re->name_entry_size);
internal_re->name_count = byteflip2(re->name_count);

if (study != NULL)
  {
  *internal_study = *study;   /* To copy other fields */
  internal_study->size = byteflip4(study->size);
  internal_study->options = byteflip4(study->options);
  }

return internal_re;
}