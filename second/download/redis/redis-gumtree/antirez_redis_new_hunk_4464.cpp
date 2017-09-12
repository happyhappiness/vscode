                addReply(c,shared.nullbulk);
            } else {
                robj *ele = listNodeValue(ln);
                addReplyBulkLen(c,ele);
                addReply(c,ele);
                addReply(c,shared.crlf);
            }
