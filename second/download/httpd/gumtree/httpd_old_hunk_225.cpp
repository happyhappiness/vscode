        if (str[i] == '\n') {
            i++;
            break;
        }
    }
    str[i] = 0;
    return rv;
}



APR_DECLARE_NONSTD(int) apr_file_printf(apr_file_t *fptr, 
