#include <cstdint>

#include <atomic>
#include <array>
#include <tuple>
#include <utility>

#include <immintrin.h>
#include <pthread.h>

#ifndef ZEFFA9F55_2AF8_4DD5_8FDD_9259974DAC6D
#define ZEFFA9F55_2AF8_4DD5_8FDD_9259974DAC6D

constexpr auto cache_line_size = 64;

template <size_t N>
using padding = std::array<uint8_t, N>;

void yield_execution()
{ _mm_pause(); }

#include <examples/relacy.hpp>
#include <examples/create_thread.hpp>

#endif
