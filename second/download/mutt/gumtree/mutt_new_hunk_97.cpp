int mutt_parse_unscore (BUFFER *, BUFFER *, unsigned long, BUFFER *);
int mutt_parse_unhook (BUFFER *, BUFFER *, unsigned long, BUFFER *);
int mutt_pattern_func (int, char *);
int mutt_pipe_attachment (FILE *, BODY *, const char *, char *); 
int mutt_print_attachment (FILE *, BODY *);
int mutt_query_complete (char *, size_t);
int mutt_query_variables (LIST *queries);
int mutt_save_attachment (FILE *, BODY *, char *, int, HEADER *);
int _mutt_save_message (HEADER *, CONTEXT *, int, int, int);
int mutt_save_message (HEADER *, int, int, int, int *);
int mutt_search_command (int, int);
#ifdef USE_SMTP
int mutt_smtp_send (const ADDRESS *, const ADDRESS *, const ADDRESS *,
                    const ADDRESS *, const char *, int);
#endif
int mutt_wstr_trunc (const char *, size_t, size_t, size_t *);
int mutt_charlen (const char *s, int *);
int mutt_strwidth (const char *);
int mutt_compose_menu (HEADER *, char *, size_t, HEADER *);
int mutt_thread_set_flag (HEADER *, int, int, int);
int mutt_user_is_recipient (HEADER *);
void mutt_update_num_postponed (void);
int mutt_wait_filter (pid_t);
int mutt_which_case (const char *);
int mutt_write_fcc (const char *path, HEADER *hdr, const char *msgid, int, char *);
int mutt_write_mime_body (BODY *, FILE *);
int mutt_write_mime_header (BODY *, FILE *);
int mutt_write_one_header (FILE *fp, const char *tag, const char *value, const char *pfx, int wraplen, int flags);
int mutt_write_rfc822_header (FILE *, ENVELOPE *, BODY *, int, int);
void mutt_write_references (LIST *, FILE *, int);
int mutt_yesorno (const char *, int);
void mutt_set_header_color(CONTEXT *, HEADER *);
void mutt_sleep (short);
int mutt_save_confirm (const char  *, struct stat *);

int mh_valid_message (const char *);
