#include "string_view.h"
#include <cstring>

StringView::StringView() : str_(nullptr) {}
StringView::StringView(const char *str) : str_(str), size_(std::strlen(str)) {}
StringView::StringView(const char *str, const size_t size) : str_(str), size_(size) {}

const char &StringView::operator[](size_t i) const {
  return *(str_ + i);
}

const char &StringView::Front() const {
  return *str_;
}

const char &StringView::Back() const {
  return *(str_ + size_ - 1);
}

size_t StringView::Size() const {
  return size_;
}

size_t StringView::Length() const {
  return size_;
}

bool StringView::Empty() const {
  return (size_ == 0);
}

const char *StringView::Data() const {
  return str_;
}

void StringView::Swap(StringView &other) {
  auto tmp_str = str_;
  str_ = other.str_;
  other.str_ = tmp_str;

  auto temp_size = size_;
  size_ = other.size_;
  other.size_ = temp_size;
}

void StringView::RemovePrefix(size_t prefix_size) {
  str_ += prefix_size;
  size_ -= prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) {
  size_ -= suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count = -1) {
  size_t new_len = 0;
  if (Size() - pos < count) {
    new_len = Size() - pos;
  } else {
    new_len = count;
  }
  StringView new_str(str_ + pos, new_len);
  return new_str;
}
