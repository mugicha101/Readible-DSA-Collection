#include "skiplist.h"
#include <iostream>

#define print(container) std::cout << "size " << container.size() << ": "; for (auto x : container) std::cout << x << " "; std::cout << std::endl

int main(int argc, char *argv[]) {
  SkipList<int, 10> sl;
  print(sl);
  srand(0);
  for (int i = 0; i < 10; ++i) {
    int val = rand() % 100;
    std::cout << "insert " << val << std::endl;
    sl.insert(val);
    print(sl);
  }
  for (int i = 0; i < 10; ++i) {
    int val = rand() % 100;
    std::cout << "erase " << val << " -> " << sl.erase(val) << std::endl;
    print(sl);
  }
  std::cout << "clear" << std::endl;
  sl.clear();
  print(sl);
}