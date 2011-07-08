//
// Copyright (c) 2011 Kim Walisch, <kim.walisch@gmail.com>.
// All rights reserved.
//
// This file is part of primesieve.
// Visit: http://primesieve.googlecode.com
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//   * Redistributions of source code must retain the above copyright
//     notice, this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above
//     copyright notice, this list of conditions and the following
//     disclaimer in the documentation and/or other materials provided
//     with the distribution.
//   * Neither the name of the modp.com nor the names of its
//     contributors may be used to endorse or promote products derived
//     from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef PRESIEVE_H
#define PRESIEVE_H

#include "defs.h"

/**
 * PreSieve objects are used to reset the sieve array (set bits to 1)
 * of SieveOfEratosthenes objects after each sieved segment and to
 * pre-sieve multiples of small primes <= limit_.
 * The idea is to create a wheel array in which multiples of small
 * primes are crossed off at initialization.
 * After each sieved segment the wheel array is copied to the sieve in
 * order to reset it and remove the multiples of small primes.
 * Pre-sieving multiples of small primes (e.g. <= 19) speeds up my
 * sieve of Eratosthenes implementation by about 20 percent when
 * sieving < 10^10.
 *
 * Pre-sieving multiples of small primes is described in more detail
 * in Joerg Richstein's German doctoral thesis:
 * "Segmentierung und Optimierung von Algorithmen zu Problemen aus der Zahlentheorie", Gie�en, Univ., Diss., 1999
 * 3.3.5 Vorsieben kleiner Primfaktoren
 * http://geb.uni-giessen.de/geb/volltexte/1999/73/pdf/RichsteinJoerg-1999-08-06.pdf
 *
 * == Memory Usage ==
 * 
 * PreSieve uses: primeProduct(limit_)/30 Bytes of memory.
 *
 * PreSieve multiples of primes <= 11 uses 77 Bytes
 * PreSieve multiples of primes <= 13 uses 1001 Bytes
 * PreSieve multiples of primes <= 17 uses 16.62 Kilobytes
 * PreSieve multiples of primes <= 19 uses 315.75 KiloBytes
 * PreSieve multiples of primes <= 23 uses 7.09 Megabytes
 */
class PreSieve {
public:
  PreSieve(uint32_t);
  ~PreSieve();
  uint32_t getLimit() const {
    return limit_;
  }
  void doIt(uint8_t*, uint32_t, uint64_t) const;
private:
  static const uint32_t smallPrimes_[9];
  /** Multiples of small primes <= limit_ (MAX 23) are pre-sieved. */
  uint32_t limit_;
  /** Product of the primes <= limit_. */
  uint32_t primeProduct_;
  /**
   * Wheel array of size primeProduct(limit_)/30 in which multiples of
   * small primes <= limit_ are crossed off.
   */
  uint8_t* wheelArray_;
  /** Size of wheelArray_. */
  uint32_t size_;
  uint32_t getPrimeProduct(uint32_t) const;
  void initWheelArray();
};

#endif /* PRESIEVE_H */
