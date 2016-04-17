/*
 * SMART: string matching algorithms research tool.
 * Copyright (C) 2012  Simone Faro and Thierry Lecroq
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 * 
 * contact the authors at: faro@dmi.unict.it, thierry.lecroq@univ-rouen.fr
 * download the tool at: http://www.dmi.unict.it/~faro/smart/
 *
 * This is an implementation of the Two Way Shift And algorithm
 * in B.Durian, T. Chhabra, S.S. Ghuman, T. Hirvola, H. Peltola, and J. Tarhio. 
 * Improved Two-Way Bit-parallel Search, 
 * in Proceedings of the Prague Stringology Conference 2014
 */

#include "include/define.h"
#include "include/main.h"
#include <memory.h>
#include <smmintrin.h>
#include <inttypes.h>

void preSA(unsigned char *x, int m, unsigned int S[]) { 
   unsigned int j, lim; 
   int i; 
   for (i = 0; i < SIGMA; ++i) S[i] = 0; 
   for (i = 0, j = 1; i < m; ++i, j <<= 1) { 
      S[x[i]] |= j; 
   } 
} 

int search(unsigned char *x, int m, unsigned char *y, int n) { 
   unsigned int I, lim, D; 
   unsigned int S[SIGMA], F; 
   int i, j, count; 
   //if (m > WORD) return search_large(x,m,y,n);

   BEGIN_PREPROCESSING
   preSA(x, m, S); 
   F = 1<<(m-1);
   I = ~0;
   END_PREPROCESSING

   BEGIN_SEARCHING
   count = 0;
   for (i = m-1; i < n; i+=m) { 
      D = S[y[i]];
      j = 1;
      while(D>0 && j<m) {
      	D = D & (((S[y[i-j]+1])<<j) & ((S[y[i+j]]>>j) | I<<(m-j)));
      	j = j+1;
      }
      if(D>0) count ++;//= _mm_popcnt_u32( D );; // count+=popcount(D);
   } 
   END_SEARCHING
   return count;
} 

/*
 * Shift And algorithm designed for large patterns
 * The present implementation searches for prefixes of the pattern of length 32.
 * When an occurrence is found the algorithm tests for the whole occurrence of the pattern
 */

int search_large(unsigned char *x, int m, unsigned char *y, int n) { 
   unsigned int lim, D,k,h,p_len; 
   unsigned int S[SIGMA], F; 
   int j, count; 

   p_len = m;
   m=32;

   /* Preprocessing */ 
   preSA(x, m, S); 
   F = 1<<(m-1);

   /* Searching */ 
   count = 0;
   for (D = 0, j = 0; j < n; ++j) { 
      D = ((D<<1)|1) & S[y[j]]; 
      if (D & F) {
         k = 0;
         h = j-m+1;
         while(k<p_len && x[k]==y[h+k]) k++;
         if(k==p_len) OUTPUT(j - m + 1); 
      }
   } 
   return count;
} 

