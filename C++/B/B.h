#ifndef STRINGV
#define STRINGV
#include <iostream>

class StringView {
public:
  const char *str_;
  size_t size_;
  StringView();
  StringView(const char* string);  // NOLINT
  StringView(const char* string, size_t size);
  const char& operator[](size_t index) const;
  const char& Front() const;
  const char& Back() const;
  size_t Size() const;
  size_t Length() const;
  bool Empty() const;
  const char* Data() const;
  void Swap(StringView& other);
  void RemovePrefix(size_t prefix_size);
  void RemoveSuffix(size_t suffix_size);
  StringView Substr(size_t pos, size_t count);
};

#endif
