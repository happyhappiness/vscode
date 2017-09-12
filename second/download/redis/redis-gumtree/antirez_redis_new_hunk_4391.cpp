            if (!de) {
                addReply(c,shared.nullbulk);
            } else {
                double *score = dictGetEntryVal(de);

                addReplyDouble(c,*score);
            }
        }
    }
