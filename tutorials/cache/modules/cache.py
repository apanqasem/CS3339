from pprint import pprint

class Entry:
    def __init__(self):
        self.valid = 0;
        self.tag = 0;
        self.ref = 0;

    def set_tag(self, tag):
        self.tag = tag

    def get_tag(self):
        return self.tag

    def set_valid(self, valid):
        self.valid = valid

    def get_valid(self):
        return self.valid

    def set_ref(self, ref):
        self.ref = ref

    def get_ref(self):
        return self.ref
        
    def display(self):
        if (self.get_valid() == 0):
            print("| " + "X" + " ", end="")
        else:    
            print("| " + str(self.get_tag()) + " ", end="")
        return

#    def __del__(self):
#        print("Deleting entry object")
               
class Cache:
    "Yoda Cache Simulator"

    def __init__(self):
        print("NULL cache created. This cache has no entries!")

    def create(self, _num_entries, _assoc):
        self.num_entries = _num_entries
        self.assoc = _assoc
        self.num_sets = (int) (_num_entries / _assoc);

        self.entries = [[Entry() for x in range(self.num_sets)] for x in range(self.assoc)]
        print("Cache created:")
        print("\t" + str(self.assoc) + "-way associative with " + str(self.num_entries) + " entries")
        print("\t" + str(self.num_sets) + " sets per way")

        for way, row in enumerate(self.entries): 
          for entry in row: 
              entry.set_tag(0)
              entry.set_valid(0)
              entry.set_ref(way)                

        self.display()

    def get_index(self, addr):
        return addr % self.num_sets

    def get_tag(self, addr):
        return (int) (addr / self.num_sets);

    def retrieve_addr(self, way, index):
        tag = self.entries[way][index].get_tag()
        return tag * self.num_sets + index; 

    def inCache(self, addr):
        index = self.get_index(addr)
        for i in self.entries: 
            if (self.entries[i][index].get_tag() == get_tag(addr)):
                return True
            return False

    def hit(self, addr):
        index = self.get_index(addr);
        for i in range(len(self.entries)): 
            if (self.entries[i][index].get_valid() == 1):
                if (self.entries[i][index].get_tag() == self.get_tag(addr)):
                    ## this is a cache hit; adjust LRU ref counter  

                    ## assoc - 1 = most recent 
                    target_ref = self.entries[i][index].get_ref()
                    for k in range(len(self.entries)):
                        ## if entry is more recent than current ref then make it older 
                        this_ref = self.entries[k][index].get_ref()
                        if (this_ref > target_ref):
                            self.entries[k][index].set_ref(this_ref - 1)
                    ## make target entry the newest entry 
                    self.entries[i][index].set_ref((self.assoc - 1));
                    print("--- [Cache Hit] Found : " + str(addr) + " in Way " + str(i) + ", Index " + str(index)) 
                    return True
                else:
                    print("--- [Cache Miss] Did not find data for addr: " + str(addr))
                    print("    Tag mismatch: Addr Tag = " + str(self.get_tag(addr)) + " Stored Tag: " + str(self.entries[i][index].get_tag()))                  return False
            else: 
                print("--- [Cache Miss] Did not find data for addr: " + str(addr))
                print("    Cache block has invalid entry ")
        return False


 
    def update(self, addr):
        self.hit(addr)
        index = self.get_index(addr)
        for i in range(len(self.entries)): 
            if (self.entries[i][index].get_ref() == 0):
                self.entries[i][index].set_valid(1)

                ## assoc - 1 = most recent
                target_ref = self.entries[i][index].get_ref()

                for k in range(len(self.entries)): 
                    ## if entry is more recent than current ref then make it older
                    this_ref = self.entries[k][index].get_ref()
                    if (this_ref > target_ref):
                        self.entries[k][index].set_ref(this_ref - 1)
                ## make target entry the newest entry ##
                self.entries[i][index].set_ref((self.assoc - 1))
#                print("--- [Cache] replacing LRU at addr: " + str(self.retrieve_addr(i, index)) + " with: " + str(addr))
                self.entries[i][index].set_tag(self.get_tag(addr))
                break

    def display(self):
        print("************ Cache ************")
        if (self.assoc == 1):
            print("+---+")
        else:
            print("+---+---+")
        for i in range(self.num_sets): 
            for j in range(self.assoc): 
                self.entries[j][i].display() 
            if (self.assoc == 1):
                print("|\n+---+")
            else:
                print("|\n+---+---+")
        print("********************************")
   
              
    def __del__(self):
        print("Deleting cache object")
        

    
    
