                    return rv;
                }
            }

            zRC = inflate(&ctx->stream, Z_NO_FLUSH);

            if (zRC == Z_STREAM_END) {
                /*
                 * We have inflated all data. Now try to capture the
                 * validation bytes. We may not have them all available
                 * right now, but capture what is there.
                 */
