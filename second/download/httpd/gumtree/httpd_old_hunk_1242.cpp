                    return HTTP_FORBIDDEN;
                }

                X509_free(peercert);
            }
        }
    }

    /*
     * Check SSLRequire boolean expressions
     */
    requires = dc->aRequirement;
