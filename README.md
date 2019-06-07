# primetest_h
A collection of header-only libraries for testing the primality of numbers. The main goal is a mix of speed and simplicity. Because of this space is basically ignored. At the moment the lowest level header contains a list of all prime numbers less than $$2^16$$. For searches under this bound a binary search is used to check membership in no more than 16 subdivisions.
