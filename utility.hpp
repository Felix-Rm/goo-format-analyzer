#pragma once

#include <memory>

namespace util {

  template<typename T>
  class span {
   public:
    span() : m_data(nullptr), m_size(0) {
    }

    span(T* data, size_t size) : m_data(data), m_size(size) {
    }

    template<size_t N>
    span(T (&array)[N]) : m_data(array), m_size(N) {
    }

    operator span<const T>() const {
      return span<const T>(m_data, m_size);
    }

    T* data() {
      return m_data;
    }

    size_t size() const {
      return m_size;
    }

    T* begin() {
      return m_data;
    }

    T* end() {
      return m_data + m_size;
    }

    T& operator[](size_t index) {
      return m_data[index];
    }

    const T& operator[](size_t index) const {
      return m_data[index];
    }

    T& front() {
      return m_data[0];
    }

    const T& front() const {
      return m_data[0];
    }

    T& back() {
      return m_data[m_size - 1];
    }

    const T& back() const {
      return m_data[m_size - 1];
    }

    span<T> subspan(size_t offset) {
      return span<T>(m_data + offset, m_size - offset);
    }

    span<T> subspan(size_t offset, size_t count) {
      return span<T>(m_data + offset, count);
    }

   private:
    T* m_data;
    size_t m_size;
  };

  template<typename T>
  class dynamic_array {
   public:
    dynamic_array(size_t size) : m_data(new T[size]), m_size(size) {
    }

    T* data() {
      return m_data.get();
    }

    size_t size() const {
      return m_size;
    }

    T* begin() {
      return m_data.get();
    }

    T* end() {
      return m_data.get() + m_size;
    }

    T& operator[](size_t index) {
      return m_data[index];
    }

    const T& operator[](size_t index) const {
      return m_data[index];
    }

    span<T> as_span() {
      return span<T>(m_data.get(), m_size);
    }

   private:
    std::unique_ptr<T[]> m_data;
    size_t m_size;
  };

}  // namespace util