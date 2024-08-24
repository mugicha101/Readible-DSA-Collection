#include "skiplist.h"
#include "vec.h"
#include <iostream>

#define print(container) std::cout << "size " << container.size() << ": "; for (auto x : container) std::cout << x << " "; std::cout << std::endl

int main(int argc, char *argv[]) {
  Vec2f vec1;
  print(vec1);
  Vec2f vec2(1, 1);
  print(vec2);
  vec1 = vec2;
  print(vec1);
  vec1[0] = 2;
  print(vec1);
  std::cout << vec1[0] << std::endl;
  std::cout << vec1.x() << std::endl;
  vec1 = {1, 2};
  vec2 = {3, 4};
  Vec2f vec3 = vec1 * vec2;
  print(vec3);
  vec3 = vec1 * 3.f;
  print(vec3);
  std::cout << vec1.dot(vec2) << std::endl;
  vec3 = vec1 / 2.f;
  print(vec3);
  vec3 = 4.f * vec2;
  print(vec3);
  vec3 = vec1.proj(vec2);
  print(vec3);
  vec3 = vec1.norm();
  print(vec3);
  std::cout << vec1.mag() << std::endl;

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