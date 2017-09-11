                serverLog(LL_NOTICE,"RDB '%s': %s",
                    (char*)auxkey->ptr,
                    (char*)auxval->ptr);
            } else {
                /* We ignore fields we don't understand, as by AUX field
                 * contract. */
