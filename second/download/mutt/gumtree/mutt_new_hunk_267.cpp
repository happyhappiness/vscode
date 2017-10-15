              fprintf (fp, "%s%s", delim, _("certification"));
              delim = _(", ");
            }
          putc ('\n', fp);
        }
    }
}


/* Show detailed information about the selected key */
static void 
verify_key (crypt_key_t *key)
