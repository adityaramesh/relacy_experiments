# Overview

This is a project that explores the capabilities of Dmitry Vyukov's [race detector][relacy] called
relacy. The goals of this project are the following:

- Gain some experience using relacy; see what it can and cannot do.
- Identify best practices for using it in both debug and release mode. Can we design a clean set of
  abstractions that allow us to use relacy in both modes, without adding too much clutter or
  otherwise reducing legibility of the source code?

# Tests

Basic concurrency tests:
- Basic test with race.
- Basic test with deadlock.
- Basic test with livelock.

Basic memory tests:
- Basic test with access to uninitialized memory.
- Basic test with access to freed memory.
- Basic test with memory leak.

# Questions

- How to escape use of relacy in contexts where we know races cannot occur, in order to accelerate
  verification?
- Just use a relaxed load to obtain a non-atomic value.
