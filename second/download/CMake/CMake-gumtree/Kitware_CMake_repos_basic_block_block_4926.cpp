{
      data=multi->easyp;
      while(data) {
        singlesocket(multi, data);
        data = data->next;
      }
    }