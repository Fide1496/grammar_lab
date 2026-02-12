#pragma once
#include <iostream>
#include <atomic>

namespace dbg {

  /// Returns a reference to a process-wide atomic flag indicating whether
  /// debug logging is enabled. Implemented with a function-local static to
  /// guarantee initialization on first use (avoids static-order fiasco).
  inline std::atomic<bool>& enabled() {
    static std::atomic<bool> on{false};
    return on;
  }

  /// Toggle debug logging at runtime.
  /// Using memory_order_relaxed because we only read/write an independent flag.
  inline void set(bool on) {
    enabled().store(on, std::memory_order_relaxed);
  }

  /// Print a value to std::cerr without a trailing newline if debugging is on.
  /// Accepts any type that supports operator<<(std::ostream&, T).
  template<class T>
  inline void log(const T& x) {
    if (enabled().load(std::memory_order_relaxed)) std::cerr << x;
  }

  /// Print a value followed by '\n' to std::cerr if debugging is on.
  /// Handy for one-line status messages (e.g., “parsed stmt OK”).
  template<class T>
  inline void line(const T& x) {
    if (enabled().load(std::memory_order_relaxed)) std::cerr << x << '\n';
  }

} // namespace dbg
