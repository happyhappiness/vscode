{
      /* now fill in the Curl_message with this info */
      msg = &data->msg;

      msg->extmsg.msg = CURLMSG_DONE;
      msg->extmsg.easy_handle = data;
      msg->extmsg.data.result = result;

      rc = multi_addmsg(multi, msg);

      multistate(data, CURLM_STATE_MSGSENT);
    }