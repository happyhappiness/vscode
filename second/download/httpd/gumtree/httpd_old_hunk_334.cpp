
        if (readlen != 1) {
            rv = APR_EOF;
            break;
        }
        
        if (str[i] == '\r' || str[i] == '\x1A')
            i--;
        else if (str[i] == '\n') {
            i++;
            break;
        }
    }
    str[i] = 0;
    return rv;
}



APR_DECLARE_NONSTD(int) apr_file_printf(apr_file_t *fptr, 
