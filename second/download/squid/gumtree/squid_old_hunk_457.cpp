                /* Again, we own this structure layout */
                rep->header.putStr(HDR_X_ACCELERATOR_VARY, vary.termedBuf());
                vary.clean();
            }

#endif
            pe->replaceHttpReply(rep);

            pe->timestampsSet();

            pe->makePublic();

            pe->complete();

            pe->unlock();
        }

        newkey = storeKeyPublicByRequest(mem_obj->request);
