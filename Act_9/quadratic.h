#ifndef QUADRATIC_H_
#define QUADRATIC_H_

#include <string>
#include <sstream>

template <class Key, class Value>
class Quadratic {
private:
  unsigned int (*func)(const Key);
  unsigned int size;
  unsigned int count;

  Key *keys;
  Key initialValue;
  Value *values;

  long indexOf(const Key) const;

public:
  Quadratic(unsigned int, Key, unsigned int (*f)(const Key));
  ~Quadratic();
  bool full() const;
  bool put(Key, Value);
  bool contains(const Key) const;
  Value get(const Key);
  void clear();
  std::string toString() const;
};

template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f)(const Key))
    : func(f), size(sze), count(0), initialValue(init) {
  keys = new Key[size];
  values = new Value[size];
  for (int i = 0; i < size; i++) {
    keys[i] = initialValue;
    values[i] = 0;
  }
}

template <class Key, class Value>
Quadratic<Key, Value>::~Quadratic() {
  size = 0;
  initialValue = "";
  func = 0;
  count = 0;
  delete[] keys;
  delete[] values;
  keys = 0;
  values = 0;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::full() const {
  if (count >= size) {
    return true;
  }
  return false;
}

template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const {
  long ind = func(k) % size;
  long start = ind;
  for (int j = 0; j < size; j++) {
    if (keys[ind] == k) {
      return ind;
    }
    ind = (start + j * j) % size;
  }

  return -1; // Si no se encuentra la llave
}

template <class Key, class Value>
bool Quadratic<Key, Value>::put(Key k, Value v) {
  if (full()) {
    return false;
  }
  long pos = func(k);
  pos = indexOf(k);
  if (pos != -1) {
    values[pos] = v;
    return true;
  }
  unsigned int start = func(k) % size;
  unsigned int i = func(k) % size;
  for (int j = 0; j < size; j++) {
    if (keys[i] == initialValue) {
      values[i] = v;
      keys[i] = k;
      return true;
    }
    i = (start + j * j) % size;
  }
  return false;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::contains(const Key k) const {
  if (indexOf(k) == -1) {
    return false;
  }
  return true;
}

template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k) {
  if (contains(k)) {
    long r = indexOf(k);
    return values[r];
  }
  return -1; // Valor no encontrado
}

template <class Key, class Value>
void Quadratic<Key, Value>::clear() {
  for (int i = 0; i < size; i++) {
    values[i] = 0;
    keys[i] = initialValue;
  }
  count = 0;
}

// Impresion clase quadratic
template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
  std::stringstream aux;
  for (int i = 0; i < size; i++) {
    if (keys[i] != initialValue) {
      aux << "(" << i << " ";
      aux << keys[i] << " : " << values[i] << ")\n";
    }
  }
  return aux.str();
}

#endif /* HASH_H_ */
