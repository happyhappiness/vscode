      this->ParsePerson(this->Line.c_str()+7, author);
      this->Rev.Author = author.Name;
      this->Rev.EMail = author.EMail;
      this->Rev.Date = this->FormatDateTime(author);
      }
    else if(strncmp(this->Line.c_str(), "committer ", 10) == 0)
      {
      Person committer;
      this->ParsePerson(this->Line.c_str()+10, committer);
      this->Rev.Committer = committer.Name;
      this->Rev.CommitterEMail = committer.EMail;
      this->Rev.CommitDate = this->FormatDateTime(committer);
      }
    }

