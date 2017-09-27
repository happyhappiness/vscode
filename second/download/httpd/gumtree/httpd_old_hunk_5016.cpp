        *cpp = SSL_X509_NAME_ENTRY_to_string(p, X509_NAME_get_entry(subj, i));
    }

    return apr_is_empty_array(*ids) ? FALSE : TRUE;
}

/*  _________________________________________________________________
**
**  Low-Level CA Certificate Loading
**  _________________________________________________________________
*/

