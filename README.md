# fs-lru-cache

This Python package uses the filesystem as a cache for potentially large objects, deleting the least recently used (LRU) when it reaches a size limit. Data are moved into the cache and are moved to the head (most recently used) position by renaming files, not copying them, and a nested directory structure is maintained to ensure that no directory contains more than a given number of files/subdirectories. The interface is a key-value store, responding to "get" requests with the _filename_ of the value. Only this key-to-filename map is explicitly in memory; the data in the files are expected to be paged into memory by the operating system.

This package was created to manage a namespace of Numpy arrays, which can often be megabytes or gigabytes per array. In our use-case, the arrays can be created on demand (usually by a network transfer and/or conversion from another format), but this is expensive. The whole collection of arrays is also too large to keep in memory, but a fast SSD disk (with TRIM and no journaling) provides up to a terabyte of local storage at a rate of hundreds of MB/second. Even faster when the operating system caches the most recent of the most recently used files as virtual memory.

## Features

   * Key-value cache that can scale to the size of a local disk.
   * Cache order is maintained in the directory structure by renaming files.
   * Directory structure is guaranteed to have no more than a given `maxperdir` files/subdirectories per directory.
   * Cache persists beyond a process's lifetime. A new process can `adopt` an old process's data (for crash recovery).
   * Cache manager and cache users may be separate processes. In this case, values are provided as hard-linked files for thread-safety.

## Limitations

   * The cache must be managed by a single thread/process. In principle, this package can be extended to support multithreaded cache management, but this was not required by our use-case.
   * The key-filename lookup table is in memory. How much memory this consumes depends on the size of the keys and therefore filenames, but a not unreasonable size of 100 bytes per string and Python dict overhead results in 250 bytes per key-filename pair: 4 million entries per gigabyte of memory. (But if files are a megabyte each, that's also 4 terabytes of data on disk, so you run out of disk space about as fast as you run out of lookup memory.)
