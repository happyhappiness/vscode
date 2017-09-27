        if (status != V_OCSP_CERTSTATUS_GOOD) {
            char snum[MAX_STRING_LEN] = { '\0' };
            BIO *bio = BIO_new(BIO_s_mem());

            if (bio) {
                int n;
                if ((i2a_ASN1_INTEGER(bio, cinf->cid->serialNumber) != -1) &&
                    ((n = BIO_read(bio, snum, sizeof snum - 1)) > 0))
                    snum[n] = '\0';
                BIO_free(bio);
            }

            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02969)
