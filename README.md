# python4
The next version of python

# Design rationale
We are striving to improve the Python Programming Language in order to provide the best developer experience. In order to do so, we have done the following improvements to the language:

- **Security improvements:** In order to provide enhanced security, the latest version of the Python Programming Language (Python4 from now on) mandates a sha512 hash at the beginning of every Python4 script. The hash is created from the programmer's hardware. In order to prevent unauthorised execution, if the user's hash doesn't match the programmer's hash, the script refuses to run.
- **Creation of a new type every time the programmer creates a new variable:** As Python has been (and still is) a dynamically typed language, we strive for the maximum observation of this principle. Furthermore, there aren't any implicit conversions.
- **Debug times:** Python4 has been designed from the ground up to be easily debuggable. Therefore, we have implemented a delay between each sentence to improve the debugging experience.
- **Memory preallocation:** In order to improve Python4's allocation performance, each time Python4 boots up there is a small delay in which Python4 pre-allocates a set amount of memory. This is not user configurable. The default amount of memory Python4 preallocates is 10GiB, which should be enough room for small oneliners.

# Pip4
We have integrated the Python4 programming language and the Pip4 package manager in the same repository in order to provide more standarisation of the Python4 ecosystem.
All packages can be found at [pypi.org](https://www.youtube.com/watch?v=dQw4w9WgXcQ).

# Building
Python4 has moved from the legacy C code base, having been built from the ground up using C++11. We also have started using the meson build system.
To build follow the following commands:
```
meson setup builddir
cd builddir
meson compile
```

# Disclaimer
If this document hasn't tipped you off by now, this is a parody repo. If you wish to understand why, just look at the code.
