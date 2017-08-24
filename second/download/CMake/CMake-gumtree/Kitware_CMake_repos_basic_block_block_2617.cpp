(!Expect('"')) {
      Expect('\\');
      this->String.append(1, C);
      Next();
    }