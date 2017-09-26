         * back end since they would in part be interpreted
         * as another request!  If nothing is sent, then
         * just send nothing.
         *
         * Prevents HTTP Response Splitting.
         */
        if (bytes_streamed > cl_val)
             continue;

        if (header_brigade) {
            /* we never sent the header brigade, so go ahead and
             * take care of that now
             */
            bb = header_brigade;
