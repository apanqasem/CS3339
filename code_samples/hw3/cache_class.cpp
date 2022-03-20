#include<iostream>
#include<fstream>

using namespace std;

class Entry {
public:
  Entry();
  ~Entry();
  void display(ofstream& outfile);

  void set_tag(int _tag) { tag = _tag; }
  int get_tag() { return tag; }

  void set_valid(bool _valid) { valid = _valid; }
  bool get_valid() { return valid; }

  void set_ref(int _ref) { ref = _ref; }
  int get_ref() { return ref; }

private:  
  bool valid;
  unsigned tag;
  int ref;
};

class Cache {
public:
  Cache(int, int);
  ~Cache();

  void display(ofstream& outfile);


  int get_index(unsigned long addr);
  int get_tag(unsigned long addr);

  unsigned long retrieve_addr(int way, int index);
  
  bool hit(ofstream& outfile, unsigned long addr);

  void update(ofstream& outfile, unsigned long addt);

  
private:
  int assoc;
  unsigned num_entries;
  int num_sets;
  Entry **entries;
};


